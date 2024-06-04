
cbuffer TransformParams : register(b1)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
};

cbuffer MATERIAL_PARAMS : register(b3)
{
    int int_0;
    int int_1;
    int int_2;
    int int_3;
    
    float hit;
    float float_1;
    float float_2;
    float float_3;
};


struct VS_IN
{
    float3 pos : POSITION;
};

struct VS_OUT
{
    float4 pos : SV_Position;
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = float4(input.pos, 1.f);
    
    output.pos = mul(output.pos, WorldMatrix);
    output.pos = mul(output.pos, ViewMatrix);
    output.pos = mul(output.pos, ProjectionMatrix);
    
    return output;
    
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    if (hit)
    {
        return float4(0, 1.0f, 0, 0);
    }
    else
    {
        return float4(1.0f, 0, 0, 0);
    }

}