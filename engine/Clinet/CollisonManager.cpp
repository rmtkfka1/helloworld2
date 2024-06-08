#include "pch.h"
#include "CollisonManager.h"
#include "BaseCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include <varargs.h>
#include "ImguiManager.h"
#include <iostream>
#include "SphereCollider.h"
#include "Core.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "SceneManger.h"
#include "Scene.h"
void CollisonManager::Init()
{
}

void CollisonManager::Update()
{
	CheckObjectCollusion();

}

void CollisonManager::Clear()
{
	_colliders.clear();
}

void CollisonManager::CheckObjectCollusion()
{
	vector<	shared_ptr<BaseCollider>> colliders = _colliders;

	shared_ptr<BaseCollider> src = colliders[0];
	
	for (int32 i = 1; i < colliders.size(); i++)
	{
		shared_ptr<BaseCollider> dest = colliders[i];

		if (src == nullptr || dest == nullptr)
		{
			return;
		}

		if (src->CheckCollusion(dest))
		{
			if (src->_collisionMap.contains(dest.get()) == false)
			{
				src->GetOwner()->OnComponentBeginOverlap(src, dest);
				dest->GetOwner()->OnComponentBeginOverlap(dest, src);
				src->_collisionMap.insert(dest.get());
				dest->_collisionMap.insert(src.get());
			}
		}

		else
		{
			if (src->_collisionMap.contains(dest.get()))
			{
				src->GetOwner()->OnComponentEndOverlap(src, dest);
				dest->GetOwner()->OnComponentEndOverlap(dest, src);
				src->_collisionMap.erase(dest.get());
				dest->_collisionMap.erase(src.get());
			}
		}
	};
	

}

void CollisonManager::CheckRayCollusion()
{


	if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::LBUTTON))
	{
 		POINT mousePos = KeyManager::GetInstance()->GetMousePos();
		vec3 pos = vec3(mousePos.x, mousePos.y, 0.0f); 
	

		vec3 nearPoint = ToWorldPosition(pos, Matrix::Identity, CameraManager::GetInstance()->S_MatView, CameraManager::GetInstance()->S_MatProjection);

		pos.z = 1.0f; 
		vec3 farPoint = ToWorldPosition(pos, Matrix::Identity, CameraManager::GetInstance()->S_MatView, CameraManager::GetInstance()->S_MatProjection);


		vec3 worldRayDir = (farPoint - nearPoint);
		worldRayDir.Normalize();

		//����������ǵ� ��ǥ��
		Ray ray = Ray(nearPoint, worldRayDir);

		float distance = 0;

		float closestDistance = FLT_MAX;
		std::shared_ptr<BaseCollider> closestCollider = nullptr;

		for (int i = 0; i < _colliders.size(); ++i)
		{

			if (_colliders[i]->GetOwner()->GetGameObjectType() != GAMEOBJECT_TYPE::Enemy)
				continue;

			if (_colliders[i]->GetColliderType() == ColliderType::Sphere)
				continue;

			std::static_pointer_cast<BoxCollider>(_colliders[i])->_hit = false;

			float distance = 0;

			if (_colliders[i]->CheckCollusion(ray, distance))
			{
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestCollider = _colliders[i];
				}
			}
		}


		if (closestCollider != nullptr)
		{
			std::static_pointer_cast<BoxCollider>(closestCollider)->_hit = true;
		}


	}
}

vec3 CollisonManager::ToWorldPosition(const vec3& pos, const Matrix& W, const Matrix& V, const Matrix& P)
{
	vec3 p = pos;

	//NDC �� �ٲ�
	p.x = 2.f * (p.x - 0) / core->GetWindowInfo().width - 1.f;
	p.y = -2.f * (p.y -0) / core->GetWindowInfo().height + 1.f;
	p.z = ((p.z - 0) / (1 - 0));

	Matrix wvp = W * V * P;

	//����ǥ�� �� ��ȯ������,  W���ٰ� ��������� ������ �׳� ������ǥ���μ�.
	Matrix wvpInv = wvp.Invert();

	p = vec3::Transform(p, wvpInv);
	return p;
}


void CollisonManager::AddCollider(shared_ptr<BaseCollider> collider)
{
	_colliders.push_back(collider);
}

void CollisonManager::RemoveCollider(shared_ptr<BaseCollider> collider)
{

	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());


}


