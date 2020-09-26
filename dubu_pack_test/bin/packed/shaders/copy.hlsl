SamplerState DefaultSampler : register(s0);
Texture2D Texture : register(t0);

struct VertexInput{
    float2 position : POSITION;
    float2 uv : TEXCOORD;
};
struct PixelInput{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};
struct PixelOutput{
    float4 color : SV_TARGET;
};

void VSMain(in VertexInput input, out PixelInput output){
    output.position = float4(input.position, 0.f, 1.f);
    output.uv = input.uv;
}

void PSMain(in PixelInput input, out PixelOutput output) {
    output.color = Texture.Sample(DefaultSampler, input.uv);
}