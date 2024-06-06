#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "Model.h"
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
}

void Player::Update()
{
	GameObject::Update();


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
