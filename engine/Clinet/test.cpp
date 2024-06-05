#include "pch.h"
#include "test.h"
#include "GameObject.h"
#include "Transform.h"
void test::Update()
{

	vec3 value =  GetOwner()->_transform->GetLocalRotation();
	vec3 value3 = GetOwner()->_transform->GetLocalPosition();
	vec3 value2 = GetOwner()->_transform->GetLook();


	if (KeyManager::GetInstance()->GetButton(KEY_TYPE::LEFT))
	{
		GetOwner()->_transform->SetLocalRotation(vec3(value.x,value.y+1,value.z));
	}
	if (KeyManager::GetInstance()->GetButton(KEY_TYPE::UP))
	{
		GetOwner()->_transform->SetLocalPosition(value3 + value2);
	}


}
