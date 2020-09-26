#include "common.hlsl"
#include "math.hlsl"

SamplerState DefaultSampler : register(s0);
Texture2D ColorTexture : register(t0);
Texture2D BackTexture : register(t1);

void VSMain(in VertexInput input, out GeometryInput output){
    output.position = input.position;
    output.uv = input.uv;
    output.tint = float4(input.tint.rgb, 1.0) * input.tint.a;
    output.blendMode = input.blendMode;
}

[maxvertexcount(4)]
void GSMain(point GeometryInput input[1], inout TriangleStream<PixelInput> output){
    float2 size = 0.5f * Stretch;
    const float4 offset[4] = {
        { -size.x, size.y, 0, 0 },
        { size.x, size.y, 0, 0 },
        { -size.x, -size.y, 0, 0 },
        { size.x, -size.y, 0, 0 },
    };

    const float2 uv[4] = {
        {input[0].uv.x, input[0].uv.y},
        {input[0].uv.x + input[0].uv.z, input[0].uv.y},
        {input[0].uv.x, input[0].uv.y + input[0].uv.w},
        {input[0].uv.x + input[0].uv.z, input[0].uv.y + input[0].uv.w},
    };

    const float2 duv = input[0].uv.zw;

    PixelInput vertex;
    for(int i = 0; i < 4; ++i){
        vertex.position = input[0].position;
        vertex.position.xy += offset[i].xy * duv;
        vertex.worldPosition = vertex.position;
        vertex.position = mul(ProjectionMatrix, vertex.position);

        vertex.uv = uv[i];
        vertex.tint = input[0].tint;
        vertex.blendMode = input[0].blendMode;

        output.Append(vertex);
    }

    output.RestartStrip();
}

void PSMain(in PixelInput input, out PixelOutput output) {
    float4 color = ColorTexture.Sample(DefaultSampler, input.uv);
    color.rgb = TO_LINEAR(color.rgb);

    float4 back = BackTexture.Sample(DefaultSampler, input.uv);
    back.rgb = TO_LINEAR(back.rgb);

    float3 col = 0.f;

    for(int lightIndex = 0; lightIndex < NumLights; ++lightIndex){
        LightData light = Lights[lightIndex];

        float dist = length(light.position - input.worldPosition.xy);

        float attenuation = 1.f / (1.0f + pow(dist / light.size, 2.0f));

        float t = Time + length(light.position);
        float flicker = cos(light.flickerSpeed * 0.732f * t) * sin(light.flickerSpeed * 1.731f * t) * 0.5f + 0.5f;

        col += saturate(attenuation) *
                saturate(1.0f - flicker * light.flickerIntensity) *
                light.intensity *
                light.color *
                lerp(color.rgb, back.rgb, light.isBackLight) * color.a;
    }

    float4 finalColor = float4(col, color.a);
    finalColor *= input.tint;
    finalColor.a *= input.blendMode;

    finalColor.rgb = TO_SRGB(finalColor.rgb);

    output.color = finalColor;
}