#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "Model.h"
#include "LightManager.h"
#include "Helper.h"
#include "CameraManager.h"
#include "SceneManger.h"
#include "Scene.h"
#include "BaseCollider.h"
#include "CollisonManager.h"
Player::Player() :GameObject(GAMEOBJECT_TYPE::Player)
{
	
}

Player::~Player()
{
	_speed = 0;
}

void Player::Init()
{
	GameObject::Init();

	LightInfo info;
	info.color.ambient = vec4(0, 0, 0, 0);
	info.color.specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	info.color.diffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	info.position = CameraManager::GetInstance()->_cameraPos;
	info.direction = CameraManager::GetInstance()->_cameraLook;
	info.lightType = static_cast<int32>(LIGHT_TYPE::SPOT_LIGHT);
	info.attenuation = Helper::GetAttenuationCoeff(10000.0f);
	LightManager::GetInstnace()->PushLight(info);

}

void Player::Update()
{
	GameObject::Update();
	vec3 direction = vec3(0, -0.1f, 0.8f);
	direction.Normalize();

	LightManager::GetInstnace()->_lightParmas.LightInfos[0].direction = direction;
	LightManager::GetInstnace()->_lightParmas.LightInfos[0].position.x = this->_transform->GetLocalPosition().x;
	LightManager::GetInstnace()->_lightParmas.LightInfos[0].position.y = this->_transform->GetLocalPosition().y+10.0f;
	LightManager::GetInstnace()->_lightParmas.LightInfos[0].position.z = this->_transform->GetLocalPosition().z;
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	{
		//스피드증가, 움직임
		if (_speed < 400.0f) {
			_speed += dt * 30;
		}

		vec3 now = _transform->GetLocalPosition();
		_transform->SetLocalPosition(vec3(now.x, now.y, now.z + _speed * dt));

	}

	{
		//좌우 키 입력 로직
		if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::LEFT))
		{

			vec3 now = _transform->GetLocalPosition();

			if (now.x > -30)
			{
				_transform->SetLocalPosition(vec3(now.x - 20, now.y, now.z));
			}
		}

		if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::RIGHT))
		{
			vec3 now = _transform->GetLocalPosition();

			if (now.x < 30)
			{
				_transform->SetLocalPosition(vec3(now.x + 20, now.y, now.z));
			}

		}

	}
	{

		if (_transform->GetLocalPosition().z > 19000.0f)
		{
			SceneManger::GetInstance()->GetCurrentScene()->_sceneEnd = true;
		}
	}

}

void Player::Render()
{
	GameObject::Render();
}

void Player::OnComponentBeginOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other)
{
	if (other->GetOwner()->GetGameObjectType() == GAMEOBJECT_TYPE::Box)
	{
		SceneManger::GetInstance()->GetCurrentScene()->ReserveDeleteGameObject(other->GetOwner());
		CollisonManager::GetInstance()->RemoveCollider(other);
		this->_speed = 0;
		CameraManager::GetInstance()->_animationflag = true;
	}

	if (other->GetOwner()->GetGameObjectType() == GAMEOBJECT_TYPE::Enemy)
	{
		SceneManger::GetInstance()->GetCurrentScene()->_sceneEnd = true;
	}
}

void Player::OnComponentEndOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other)
{

}
