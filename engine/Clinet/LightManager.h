#pragma once

enum class LIGHT_TYPE : uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};



struct LightInfo
{
	vec4		position; //������ ��ġ [ ��������Ʈ , ����Ʈ����Ʈ ] 
	vec4		direction; // ������ ���� [ ��������Ʈ , �𷺼Ƕ���Ʈ ]
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

