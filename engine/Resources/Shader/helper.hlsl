#ifndef _HELPER_HLSL_
#define _HELPER_HLSL_

#include "Common.hlsl"

LightColor CalculateLightColor(int lightIndex, float3 normal, float3 worldPos)
{
    LightColor color = (LightColor) 0.f;
    
    float distanceRatio = 1.f;
    
    if(g_light[lightIndex].lightType==0)
    {
        float Power = 0.1f;
        // Directional Light
        color.ambient = g_light[lightIndex].lightColor.ambient;
        
        float3 lightDir = normalize(-g_light[lightIndex].direction);
        
        color.diffuse = g_light[lightIndex].lightColor.diffuse * saturate(dot(lightDir, normal));
        float3 viewDir = normalize(cameraPos.xyz - worldPos);
        float3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 500.0f);
        float specularPower = 0.0f;
        color.specular = spec * g_light[lightIndex].lightColor.specular;
        
        color.diffuse *= Power;
        color.ambient *= Power;
        color.specular *= Power;
    }
    
    else if (g_light[lightIndex].lightType == 1)
    {
        //PointLight
       
        float dist = length(g_light[lightIndex].position.xyz - worldPos);
        float3 distPoly = float3(1.0, dist, dist * dist);
        
        float attenuation = 1.0 / dot(distPoly, g_light[lightIndex].attenuation);
        
        color.ambient = g_light[lightIndex].lightColor.ambient;
        
        float3 lightDir = normalize(g_light[lightIndex].position.xyz - worldPos);
        
        color.diffuse = g_light[lightIndex].lightColor.diffuse * saturate(dot(lightDir, normal));
        
        
        float3 viewDir = normalize(cameraPos.xyz - worldPos);
        float3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 500.0f);
        float specularPower = 0.0f;
        
        color.specular = specularPower*  spec * g_light[lightIndex].lightColor.specular;
        
        color.diffuse *= attenuation;
        color.ambient *= attenuation;
        color.specular *= attenuation;
    }
    else if (g_light[lightIndex].lightType == 2)
    {
   
        float3 LightDir = normalize(worldPos - g_light[lightIndex].position.xyz);
        float diffuseRatio = saturate(dot(-LightDir,normal));

        if (range == 0.f)
            distanceRatio = 0.f;
        else
        {
            float halfAngle = angle / 2;

            float3 viewLightVec = worldPos - g_light[lightIndex].position.xyz;
            float3 viewCenterLightDir = normalize(float4(g_light[lightIndex].direction));

            float centerDist = dot(viewLightVec, viewCenterLightDir);
            distanceRatio = saturate(1.f - centerDist / range);

            float lightAngle = acos(dot(LightDir, viewCenterLightDir));

            if (centerDist < 0.f || centerDist > range) // 최대 거리를 벗어났는지
                distanceRatio = 0.f;
            else if (lightAngle > halfAngle) // 최대 시야각을 벗어났는지
                distanceRatio = 0.f;
            else // 거리에 따라 적절히 세기를 조절
                distanceRatio = saturate(1.f - pow(centerDist / range, 2));
            
            
            float3 viewDir = normalize(cameraPos.xyz - worldPos);
            float3 reflectDir = reflect(-LightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 500.0f);
            float specularPower = 0.0f;
        
            color.diffuse = g_light[lightIndex].lightColor.diffuse * diffuseRatio * distanceRatio;
            color.specular = specularPower * spec * g_light[lightIndex].lightColor.specular;
            color.ambient = g_light[lightIndex].lightColor.ambient * distanceRatio;

        }
        
        
        
    }
    
  
    return color;
    
    
}

#endif