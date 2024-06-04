
cbuffer MATERIAL_PARAMS : register(b3)
{
    int int_0;
    int int_1;
    int int_2;
    int int_3;
    
    float float_0;
    float float_1;
    float float_2;
    float float_3;
};

struct VS_IN
{
    //�޽� ���� ���� �ǰ� �����ִ� �������̴�. (�޽����� �ž��ִ�������)
    float3 pos : POSITION;
    
    // �ν��Ͻ��� ���ؼ� ���������� �����ִ� �������̴�.
    row_major matrix matWorld : W;
    row_major matrix matview : V;
    row_major matrix matProjection : P;
    
    //�ν��Ͻ� ���̵������̴�.
    uint instanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_Position;
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    output.pos = float4(input.pos, 1.0f);
    output.pos = mul(output.pos, input.matWorld);
    output.pos = mul(output.pos, input.matview);
    output.pos = mul(output.pos, input.matProjection);
  

    return output;
  
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    return float4(float_0, float_1, float_2, 1.0f);
}