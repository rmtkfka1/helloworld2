#include "pch.h"
#include "Ghost.h"
#include "LightManager.h"
#include "Transform.h"
#include "Helper.h"
Ghost::Ghost():GameObject(GAMEOBJECT_TYPE::Enemy)
{
}

Ghost::~Ghost()
{
}

void Ghost::Init()
{
	GameObject::Init();

	LightInfo info;
	info.color.ambient = vec4(0.1f, 0, 0, 0);
	info.color.specular = vec4(1.0f, 0, 0, 0);
	info.color.diffuse = vec4(1.0f, 0, 0, 0);
	info.position.x = this->_transform->GetLocalPosition().x;
	info.position.y = this->_transform->GetLocalPosition().y;
	info.position.z = this->_transform->GetLocalPosition().z;
	info.lightType = static_cast<int32>(LIGHT_TYPE::POINT_LIGHT);
	info.attenuation = Helper::GetAttenuationCoeff(100000.0f);
	LightManager::GetInstnace()->PushLight(info);

}

void Ghost::Update()
{

	float dt = TimeManager::GetInstance()->GetDeltaTime();
	LightManager::GetInstnace()->_lightParmas.LightInfos[1].position.x = this->_transform->GetLocalPosition().x;
	LightManager::GetInstnace()->_lightParmas.LightInfos[1].position.y = this->_transform->GetLocalPosition().y + 10.0f;
	LightManager::GetInstnace()->_lightParmas.LightInfos[1].position.z = this->_transform->GetLocalPosition().z;

	GameObject::Update();

	_transform->SetLocalPosition(vec3(_transform->GetLocalPosition().x, _transform->GetLocalPosition().y, _transform->GetLocalPosition().z+ _speed * dt));
}

void Ghost::Render()
{
	GameObject::Render();
}

void Ghost::OnComponentBeginOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other)
{
}

void Ghost::OnComponentEndOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other)
{
}
