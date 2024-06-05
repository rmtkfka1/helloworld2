struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};

#define MAX_MODEL_TRANSFORMS 50




cbuffer BoneBuffer : register(b0)
{
    row_major matrix BoneTransforms[MAX_MODEL_TRANSFORMS];
};

cbuffer TransformParams : register(b1)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
};

cbuffer LightParams : register(b2)
{
    MaterialDesc lightColor;
  
}

cbuffer MATERIAL_PARAMS : register(b3)
{
    int normal_on;
    int specular_on;
    int boneIndex;
    int int_3;

    float float_0;
    float float_1;
    float float_2;
    float float_3;

};


Texture2D tex_0 : register(t0);
Texture2D normal_texture : register(t1);
Texture2D specular_texture : register(t2);

SamplerState sam_0 : register(s0);

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


//test ¿ë
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
    float4 color = tex_0.Sample(sam_0, input.uv);
    
    return color;
}