#include "pch.h"
#include "Lamp.h"
#include "StructedBuffer.h"

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
}

void Lamp::Update()
{
	GameObject::Update();
}

void Lamp::Render()
{
	GameObject::Render(InstanceCount, _buffer);
}
