struct VertexInput {
    float4 position : POSITION;
    float4 uv : TEXCOORD;
    float4 tint : COLOR;
    float blendMode : BLEND_MODE;
};

struct GeometryInput{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
    float4 tint : COLOR;
    float blendMode : BLEND_MODE;
};

struct PixelInput {
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION;
    float2 uv : TEXCOORD;
    float4 tint : COLOR;
    float blendMode : BLEND_MODE;
};

struct PixelOutput {
    float4 color : SV_TARGET;
};

cbuffer BufferData : register(b0) {
    float4x4 ProjectionMatrix;
    float4 Resolution;
    float2 Stretch;
    float Time;
    float1 _BufferDataPadding;
}

struct LightData{
    float2 position;
    float intensity;
    float size;
    float3 color;
    float isBackLight;
    float flickerSpeed;
    float flickerIntensity;
    float2 _padding;
};
cbuffer LightBufferData : register(b1) {
    LightData Lights[64];
    int NumLights;
    float3 _LightBufferDataPadding;
}