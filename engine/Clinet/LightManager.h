#pragma once

enum class LIGHT_TYPE : uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};





struct LightColor
{
	vec4	diffuse =vec4(1.0f,1.0f, 1.0f, 1.0f);
	vec4	ambient = vec4(0.01f, 0.01f, 0.01f, 0.01f);
	vec4	specular = vec4(1.0f, 0.647f, 0.0f, 1.0f);
};

struct LightInfo
{
	LightColor	color;
	vec4		position; //������ ��ġ [ ��������Ʈ , ����Ʈ����Ʈ ] 
	vec4		direction; // ������ ���� [ ��������Ʈ , �𷺼Ƕ���Ʈ ]
	int32	   lightType{};
	vec3       attenuation;
};

struct LightParams
{
	LightInfo	LightInfos[100];
	uint32		lightCount =0;
	int			padding1{};
	int			padding2{};
	int			padding3{};
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

	LightParams& GetParams() { return _lightParmas; }

public:
	LightParams _lightParmas;
};

