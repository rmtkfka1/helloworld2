#include "Common.hlsl"

struct instanceData
{
    row_major matrix InstnaceWorldMatrix;
};


struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    uint nInstanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;

};
    

StructuredBuffer<instanceData> instanceInfo : register(t5);


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

  
    output.pos = float4(input.pos, 1.0f);
    output.pos = mul(output.pos, instanceInfo[input.nInstanceID].InstnaceWorldMatrix);
    output.pos = mul(output.pos, ViewMatrix);
    output.pos = mul(output.pos, ProjectionMatrix);
  
    output.uv = input.uv;
    return output;
  
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = basic_texture.Sample(sam_0, input.uv);
    
    return color;
}