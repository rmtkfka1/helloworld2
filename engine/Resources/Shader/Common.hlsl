#ifndef _COMMON_HLSLI_
#define _COMMON_HLSLI_

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};

struct LightColor
{
    float4  diffuse;
    float4  ambient;
    float4  specular;
};

struct LightInfo
{
    float4 position; //광원의 위치 [ 스폿라이트 , 포인트라이트 ] 
    float4 direction; // 광원의 방향 [ 스폿라이트 , 디렉션라이트 ]
    int lightType;
    float range;
    float angle;
    int padding;
};


cbuffer LightParams :register(b0)
{
    LightColor g_lightColor;
    LightInfo g_light[100];
    int g_lightCount;
    int g_padding1;
    int g_padding2;
    int g_padding3;
};
cbuffer TransformParams : register(b1)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
};

cbuffer MaterialLight : register(b2)
{
    float4 cameraPos;
    MaterialDesc materialColor;
}


cbuffer MATERIAL_PARAMS : register(b3)
{
    int normal_on;
    int specular_on;
    int boneIndex;
    int int_3;

    float hit;
    float float_1;
    float float_2;
    float float_3;
};


Texture2D basic_texture : register(t0);
Texture2D normal_texture : register(t1);
Texture2D specular_texture : register(t2);
SamplerState sam_0 : register(s0);

#endif