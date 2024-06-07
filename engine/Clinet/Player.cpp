#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "Model.h"
#include "LightManager.h"
#include "Helper.h"
#include "CameraManager.h"
Player::Player()
{
	// -30  -10  10 30 
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
	info.attenuation = Helper::GetAttenuationCoeff(5000.0f);
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
		if (_speed < 300.0f) {
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

}

void Player::Render()
{
	GameObject::Render();
}
