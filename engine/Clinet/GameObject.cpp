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
		//�ε������� 
		// , �ν��ϼ� ���� 
		// , �����ε����� ��ġ  ex) 1000�̶�� �Է½� 1000���� �ε��������� ��ġ���� �����͸� �о� �������� ����.
		// , ������ �ε����� �������°�  ex) ���ۿ� �޽� �������� �����ص����� �������� ����Ͽ� �׷��ً� ����� .
		// , �ν��Ͻ� �ε����� �������°� 
	}

}

//COMPONET ������ ���ΰ��� 
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

