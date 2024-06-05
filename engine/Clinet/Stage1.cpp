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
#include "test.h"
#include "Lord.h"
Stage1::Stage1()
{

}

Stage1::~Stage1()
{

	CollisonManager::GetInstance()->Clear();

}

void Stage1::Init()
{


	CameraManager::GetInstance()->Init();

	{

		shared_ptr<Lord> lord = make_shared<Lord>();

		shared_ptr<Model> model = Model::ReadData(L"road/road");
		lord->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		lord->SetTransform(transform);
		AddGameObject(lord);
	}

	{
		shared_ptr<GameObject> player = make_shared<GameObject>();

		shared_ptr<Model> model = Model::ReadData(L"car/car");
		player->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		player->SetTransform(transform);
		player->_transform->SetLocalScale(vec3(0.1f, 0.1f, 0.1f));
		player->_transform->SetLocalPosition(vec3(-30.0f, 2.0f, 0));
		player->_transform->SetLocalRotation(vec3(0, 180.0f, 0));
		shared_ptr<BoxCollider> box = make_shared<BoxCollider>();
		player->AddComponent(box);

		shared_ptr<test> t = make_shared<test>();

		player->AddComponent(t);

		AddGameObject(player);
	}

	Super::Init();

}

void Stage1::Update()
{
	Super::Update();
	CameraManager::GetInstance()->Update();
}

void Stage1::LateUpdate() 
{
	Super::LateUpdate();

	//�浹ü ������Ʈ
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


