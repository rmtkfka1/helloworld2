#ifndef _HELPER_HLSL_
#define _HELPER_HLSL_

#include "Common.hlsl"

LightColor CalculateLightColor(int lightIndex, float3 normal, float3 worldPos)
{
    LightColor color = (LightColor) 0.f;
    
    float diffuseRatio = 0.f;
    float specularRatio = 0.f;
    float distanceRatio = 1.f;
    float3 LightDir = (float3) 0.f;
    if(g_light[lightIndex].lightType==0)
    {
        //// Directional Light
        //color.ambient = g_light[lightIndex].lightColor.ambient;
        
        //float3 lightDir = normalize(-g_light[lightIndex].direction);
        
        //color.diffuse = g_light[lightIndex].lightColor.diffuse * saturate(dot(lightDir, normal));
        //float3 viewDir = normalize(cameraPos.xyz - worldPos);
        //float3 reflectDir = reflect(-lightDir, normal);
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 500.0f); 
        //float specularPower = 0.0f;
        //color.specular =  spec * g_light[lightIndex].lightColor.specular;
        
    }
    
    else if (g_light[lightIndex].lightType == 1)
    {
        //PointLight
        LightDir = normalize(worldPos - g_light[lightIndex].position.xyz);
        diffuseRatio = saturate(dot(-LightDir, normal));

        float dist = distance(worldPos, g_light[lightIndex].position.xyz);
        if (g_light[lightIndex].range == 0.f)
            distanceRatio = 0.f;
        else
            distanceRatio = saturate(1.f - pow(dist / g_light[lightIndex].range, 2));
        
        
    }
    
 
    color.diffuse = g_light[lightIndex].lightColor.diffuse * diffuseRatio * distanceRatio;
    return color;
}



#endif