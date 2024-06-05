#include "pch.h"
#include "Stage1.h"
#include "Core.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "SceneManger.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "Helper.h"
#include "Material.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "ImguiManager.h"
#include "BoxCollider.h"
#include "CollisonManager.h"
#include "ObjectManager.h"
#include "SphereCollider.h"

Stage1::Stage1()
{

}

Stage1::~Stage1()
{

	CollisonManager::GetInstance()->Clear();

}

void Stage1::Init()
{
	Super::Init();
	CameraManager::GetInstance()->Init();

	{

		shared_ptr<GameObject> player = make_shared<GameObject>();

		shared_ptr<Model> model = Model::ReadData(L"Tank/Tank");
		player->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		player->SetTransform(transform);
		AddGameObject(player);
	}



}

void Stage1::Update()
{
	Super::Update();
	CameraManager::GetInstance()->Update();
}

void Stage1::LateUpdate() 
{
	Super::LateUpdate();

	//충돌체 업데이트
	CollisonManager::GetInstance()->Update();
}

void Stage1::Render()
{
	Super::Render();
}

void Stage1::ClearScene()
{
	Super::ClearScene();

}


