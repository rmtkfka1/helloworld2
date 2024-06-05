#include "pch.h"
#include "Lord.h"
#include "StructedBuffer.h"
#include "Core.h"
#include "Component.h"
#include "Model.h"
#include "Mesh.h"
#include "Transform.h"
#include "TableHeap.h"
#include "Material.h"

Lord::Lord()
{
}

Lord::~Lord()
{
}

void Lord::Init()
{

	GameObject::Init();

	_data.resize(InstanceCount);

	_buffer = make_shared<StructedBuffer>();
	_buffer->Init(sizeof(LordInstance::InstanceData), InstanceCount);

	for (int i = 0; i < InstanceCount; ++i)
	{
		_data[i].worldmat = Matrix::CreateTranslation(vec3(0, 0, i* _model->GetSize().z *2));
	}

	_buffer->PushData((_data.data()));
}

void Lord::Update()
{
	GameObject::Update();
}

void Lord::Render()
{
	GameObject::Render(InstanceCount, _buffer);
}

