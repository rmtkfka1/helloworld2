#ifndef _COMMON_HLSLI_
#define _COMMON_HLSLI_

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};


cbuffer Lightinfo : register(b0)
{
    float4 lightDirection;
    float4 cameraPos;
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