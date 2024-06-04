#include "pch.h"
#include "SunScript.h"
#include "ImguiManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TimeManager.h"
void SunScript::Update()
{
	float dt  = TimeManager::GetInstance()->GetDeltaTime();
	_lotate += 30.0f *dt ;
	GetOwner()->_transform->SetLocalRotation(vec3(0, _lotate, 0));
}
