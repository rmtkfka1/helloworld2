
#include "Common.hlsl"




struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    
    
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINOMARL;
};




VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    output.pos = float4(input.pos, 1.0f);
    output.pos = mul(output.pos, WorldMatrix);
    output.pos = mul(output.pos, ViewMatrix);
    output.pos = mul(output.pos, ProjectionMatrix);
    
    output.uv = input.uv;

    output.normal = normalize(mul(float4(input.normal, 0.0f), WorldMatrix).xyz);
    output.tangent = normalize(mul(float4(input.tangent, 0.0f), WorldMatrix).xyz);
    output.binormal = normalize(cross(output.tangent, output.normal));
    
    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = basic_texture.Sample(sam_0, input.uv);
    

    
    
     return color;
}