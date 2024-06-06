#include "pch.h"
#include "Lamp.h"
#include "StructedBuffer.h"
#include "LightManager.h"
#include "Model.h"
Lamp::Lamp()
{
}

Lamp::~Lamp()
{
}

void Lamp::Init()
{
	GameObject::Init();

	_data.resize(InstanceCount);

	_buffer = make_shared<StructedBuffer>();
	_buffer->Init(sizeof(InstanceData), InstanceCount);

	for (int i = 0; i < 20; ++i)
	{
		_data[i].worldmat =
			Matrix::CreateScale(0.03f, 0.03f, 0.03f) * Matrix::CreateTranslation(vec3(-45.0f, 15.0f, i * 1000));
	}

	for (int i = 20; i < InstanceCount; ++i)
	{
		_data[i].worldmat =
			Matrix::CreateScale(0.03f, 0.03f, 0.03f) * Matrix::CreateTranslation(vec3(45.0f, 15.0f, -(20-i)* 1000));
	}

	_buffer->PushData((_data.data()));


	for (int i = 0; i < InstanceCount; ++i)
	{
		LightInfo info;
		info.position.x = _data[i].worldmat.Translation().x;
		info.position.y = _data[i].worldmat.Translation().y;
		info.position.z = _data[i].worldmat.Translation().z;
		info.lightType = static_cast<int32>(LIGHT_TYPE::POINT_LIGHT);
		info.range = 300.0f;
		LightManager::GetInstnace()->PushLight(info);
	}

	//LightInfo info;
	//info.direction = vec4(0, -1.0f, -1.0f, 0);
	//info.lightType = static_cast<int32>(LIGHT_TYPE::DIRECTIONAL_LIGHT);
	//LightManager::GetInstnace()->PushLight(info);

}

void Lamp::Update()
{
	GameObject::Update();
}

void Lamp::Render()
{
	GameObject::Render(InstanceCount, _buffer);
}
