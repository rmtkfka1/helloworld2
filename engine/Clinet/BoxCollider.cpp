#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Core.h"
#include "TableHeap.h"
#include "ImguiManager.h"
#include "ResourceManager.h"
#include "SphereCollider.h"
#include "ConstantBuffer.h"
bool BoxCollider::_colliderRender = true;

BoxCollider::BoxCollider():BaseCollider(ColliderType::Box)
{



}

BoxCollider::~BoxCollider()
{
      int a = 5;
}

void BoxCollider::Init()
{
	

}

void BoxCollider::Update()
{
	auto onwerTransform = GetOwner()->_transform;

	_orginbox.Transform(_box, onwerTransform->GetMatrix());
	//_box.Orientation = Quaternion::CreateFromYawPitchRoll(onwerTransform->GetLocalRotation().x,
	//	onwerTransform->GetLocalRotation().y,
	//	onwerTransform->GetLocalRotation().z);

}

void BoxCollider::Render()
{

	if (_colliderRender)
	{
		_shader->SetPipelineState();

		core->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		core->GetCmdList()->IASetVertexBuffers(0, 1, &_mesh->GetVertexView());
		core->GetCmdList()->IASetIndexBuffer(&_mesh->GetIndexView());

		GetOwner()->_transform->Update();

		if (_hit)
		{
			_params.Setfloat(0, 1);
		}
		else
		{
			_params.Setfloat(0, 0);
		}

		core->GetConstantBuffer(CBV_REGISTER::b3)->PushData(&_params, sizeof(_params));

		core->GetTableHeap()->SetGraphicsRootDescriptorTable();

		core->GetCmdList()->DrawIndexedInstanced(_mesh->GetIndexCount(), 1, 0, 0, 0);
	}

}

bool BoxCollider::CheckCollusion(shared_ptr<BaseCollider>& other)
{
	ColliderType type = other->GetColliderType();

	switch (type)
	{
	case ColliderType::Box:
		return _box.Intersects(static_pointer_cast<BoxCollider>(other)->GetBox());
		break;
	case ColliderType::Sphere:
		return _box.Intersects(static_pointer_cast<SphereCollider>(other)->GetSphere());
		break;
	default:
		break;
	}

	return false;
	
}

bool BoxCollider::CheckCollusion(Ray& ray, OUT float& distance)
{
	return _box.Intersects(ray.position, ray.direction, OUT distance);
}



void BoxCollider::MakeBoundingBox()
{

	ShaderInfo info;

	info.rasterizerType = { RASTERIZER_TYPE::WIREFRAME };

	_shader = ResourceManager::GetInstance()->LoadShader(L"BoundingBox.hlsl", L"BoundingBox.hlsl", info);
	_mesh = make_shared<Mesh>();

	_box.Center = this->GetCenter();
	_box.Extents = this->GetSize();

	_orginbox.Center = this->GetCenter();
	_orginbox.Extents = this->GetSize();

	Update();

    vector<Vertex> vec(8);
	vec[0].position = vec3(_totalCenter.x - _totalSize.x , _totalCenter.y + _totalSize.y , _totalCenter.z - _totalSize.z );
	vec[1].position = vec3(_totalCenter.x + _totalSize.x , _totalCenter.y + _totalSize.y , _totalCenter.z - _totalSize.z );
	vec[2].position = vec3(_totalCenter.x - _totalSize.x , _totalCenter.y - _totalSize.y , _totalCenter.z - _totalSize.z );
	vec[3].position = vec3(_totalCenter.x + _totalSize.x , _totalCenter.y - _totalSize.y , _totalCenter.z - _totalSize.z );

	vec[4].position = vec3(_totalCenter.x - _totalSize.x , _totalCenter.y + _totalSize.y , _totalCenter.z + _totalSize.z );
	vec[5].position = vec3(_totalCenter.x + _totalSize.x , _totalCenter.y + _totalSize.y , _totalCenter.z + _totalSize.z );
	vec[6].position = vec3(_totalCenter.x - _totalSize.x , _totalCenter.y - _totalSize.y , _totalCenter.z + _totalSize.z );
	vec[7].position = vec3(_totalCenter.x + _totalSize.x , _totalCenter.y - _totalSize.y , _totalCenter.z + _totalSize.z );
	
	vector<uint32> index(36);

	//�ո�
	index[0] = 0; 	index[1] = 1; 	index[2] = 3;
	index[3] = 2; 	index[4] = 0; 	index[5] = 3;

	//���ʸ�
	index[6] = 4; 	index[7] = 0; 	index[8] = 2;
	index[9] = 6; 	index[10] =4; 	index[11] = 2;

	//�޸�
	index[12] = 5; 	index[13] = 4; 	index[14] = 6;
	index[15] = 7; 	index[16] = 5; 	index[17] = 6;

	//�����ʸ�
	index[18] = 1; 	index[19] = 5; 	index[20] = 7;
	index[21] = 3; 	index[22] = 1; 	index[23] = 7;

	//����
	index[24] = 4; 	index[25] = 5; 	index[26] = 1;
	index[27] = 0; 	index[28] = 4; 	index[29] = 1;

	//�Ʒ���
	index[30] = 2; 	index[31] = 3; 	index[32] = 7;
	index[33] = 6; 	index[34] = 2; 	index[35] = 7;

	_mesh->Init(vec, index);

}
