#include "pch.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Core.h"
#include "TableHeap.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include "CameraManager.h"
#include "Material.h"
#include "Model.h"
#include "ImguiManager.h"
#include "Scripts.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CollisonManager.h"
#include "SphereCollider.h"



GameObject::GameObject()
{
	_type = GAMEOBJECT_TYPE::None;
}

GameObject::GameObject(GAMEOBJECT_TYPE type):_type(type)
{

}


GameObject::~GameObject()
{
}

void GameObject::Init()
{

	for (auto& compoent : _component)
	{
		compoent->Init();
	}

}

void GameObject::Update()
{
	for (auto& compoent : _component)
	{
		compoent->Update();
	}

}



void GameObject::Render()
{

	for (auto& compoent : _component)
	{
		compoent->Render();
	}

	vector<shared_ptr<ModelMesh>>& meshData = _model->GetMeshes();

	for (auto& data : meshData)
	{
		core->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		core->GetCmdList()->IASetVertexBuffers(0, 1, &data->meshes->GetVertexView());
		core->GetCmdList()->IASetIndexBuffer(&data->meshes->GetIndexView());

	
		_transform->Update();

		if (data->material)
		{
			data->material->Update();
		}

		core->GetTableHeap()->SetGraphicsRootDescriptorTable();
		core->GetCmdList()->DrawIndexedInstanced(data->meshes->GetIndexCount(), 1, 0, 0, 0); 
		//인덱스갯수 
		// , 인스턴수 갯수 
		// , 시작인덱스의 위치  ex) 1000이라고 입력시 1000번쨰 인덱스버퍼의 위치부터 데이터를 읽어 렌더링에 사용됨.
		// , 각정점 인덱스에 더해지는값  ex) 버퍼에 메쉬 여러개를 저장해뒀을때 오프셋을 사용하여 그려줄떄 사용함 .
		// , 인스턴스 인덱스에 더해지는값 
	}

}

//COMPONET 이지만 따로관리 
void GameObject::SetTransform(shared_ptr<Transform> transform)
{
	_transform = transform;
	_transform->SetTotalCenter(_totalCenter);
	_transform->SetSize(_totalSize);

}



void GameObject::SetModel(shared_ptr<Model> model)
{
	_totalCenter = model->GetCenter();
	_totalSize = model->GetSize();
	_totalRadius = model->GetRadius();
	_model = model;
}



////////////////////////////////////////////////

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetOwner(shared_from_this());

	if (component->GetComponentType()== COMPONENT_TYPE::COLLIDER)
	{
		if (static_pointer_cast<BaseCollider>(component)->GetColliderType() == ColliderType::Box)
		{
			static_pointer_cast<BoxCollider>(component)->SetTotalCenter(this->_totalCenter);
			static_pointer_cast<BoxCollider>(component)->SetSize(this->_totalSize);
			static_pointer_cast<BoxCollider>(component)->MakeBoundingBox();
			CollisonManager::GetInstance()->AddCollider(static_pointer_cast<BoxCollider>(component));
			_collider = static_pointer_cast<BoxCollider>(component);
		}

		else if (static_pointer_cast<BaseCollider>(component)->GetColliderType() == ColliderType::Sphere)
		{
			shared_ptr<SphereCollider> collider = static_pointer_cast<SphereCollider>(component);
			collider->SetTotalCenter(this->_totalCenter);
			collider->SetRadius(this->_totalRadius);
			collider->MakeBoundingSphere();
			CollisonManager::GetInstance()->AddCollider(collider);
			_collider = collider;
		}
	}


	_component.push_back(component);
}


void GameObject::OnComponentBeginOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other)
{


}
void GameObject::OnComponentEndOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other)
{


}

