#pragma once

enum class LIGHT_TYPE : uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};



struct LightInfo
{
	vec4		position; //광원의 위치 [ 스폿라이트 , 포인트라이트 ] 
	vec4		direction; // 광원의 방향 [ 스폿라이트 , 디렉션라이트 ]
	int32		lightType;
	float		range;
	float		angle;
	int32		padding;
};

struct LightColor
{
	vec4	diffuse;
	vec4	ambient;
	vec4	specular;
};

struct LightParams
{
	LightColor	color; 
	LightInfo	LightInfos[100];
	uint32		lightCount;
	int32		padding1;
	int32		padding2;
	int32		padding3;
};

class LightManager
{

public:
	static LightManager* GetInstnace()
	{
		static LightManager Manager;
		return &Manager;
	}

	void PushLight(LightInfo info);
	void SetData();

private:
	LightParams _lightParmas;
};

