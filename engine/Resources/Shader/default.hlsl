
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


//test øÎ
static float4 power = { 1.0f, 1.0f, 1.0f, 1.0f };
static float sh = 14.0f;

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
    
    float3 normal = normalize(input.normal);
    float3 lightDir = normalize(lightDirection.xyz);
    
    //≥Î∏ª∏≈«Œ
    if (normal_on)
    {
        float3 tagentSpaceNormal = normal_texture.Sample(sam_0, input.uv).xyz;
        
        tagentSpaceNormal = (tagentSpaceNormal - 0.5f) * 2.f;
    
        float3x3 matTBN = { input.tangent, input.binormal, input.normal };
    
        normal = normalize(mul(tagentSpaceNormal, matTBN));
    }
    
  
    // µ«ª¡Ó ∆—≈Õ
    float4 diffuseFactor = saturate(dot(normal, -lightDir)) * lightColor.diffuse * color;
    
    // æ⁄∫Òæ∆Æ ∆—≈Õ
    float4 ambientFactor = lightColor.ambient * color;
    
    // Ω∫∆Â≈ß∑Ø ∆—≈Õ
    float3 reflection = reflect(-lightDir, normal);
    float3 viewDir = normalize(cameraPos.xyz - input.pos.xyz);
    float specFactor = pow(saturate(dot(reflection, viewDir)), sh);
    float4 specularFactor = specFactor * lightColor.specular;
    
    if (specular_on)
    {
        specularFactor *= specular_texture.Sample(sam_0, input.uv);
    }
    
    // ∆—≈Õ ∞·«’
    float4 totalColor = diffuseFactor + ambientFactor + specularFactor;
    
    return color;
}