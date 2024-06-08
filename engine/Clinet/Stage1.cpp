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
#include "Lord.h"
#include "Player.h"
#include "Lamp.h"
#include "LightManager.h"
#include "Box.h"
#include <random>
#include "Ghost.h"

default_random_engine dre;
uniform_int_distribution<int> uid(0, 3);
uniform_real_distribution<float> uidZ(0, 18000.0f);

Stage1::Stage1()
{

}

Stage1::~Stage1()
{
	LightManager::GetInstnace()->_lightParmas.lightCount = 0;
	CollisonManager::GetInstance()->Clear();

}

void Stage1::Init()
{


	CameraManager::GetInstance()->Init();
	

	{
		shared_ptr<Player> player = make_shared<Player>();

		shared_ptr<Model> model = Model::ReadData(L"car/car");
		player->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		player->SetTransform(transform);
		player->_transform->SetLocalScale(vec3(0.1f, 0.1f, 0.1f));
		player->_transform->SetLocalPosition(vec3(-30.0f, 2.0f, 0));
		player->_transform->SetLocalRotation(vec3(0, 180.0f, 0));
		shared_ptr<BoxCollider> box = make_shared<BoxCollider>();
		player->AddComponent(box);
		ObjectManager::GetInstance()->player = player.get();

		AddGameObject(player);
	}

	{

		shared_ptr<Ghost> lord = make_shared<Ghost>();

		shared_ptr<Model> model = Model::ReadData(L"horror/horror");
		lord->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		lord->SetTransform(transform);
		lord->_transform->SetLocalRotation(vec3(0, 180.0f, 0));
		lord->_transform->SetLocalPosition(vec3(0, 0, -2000.0f));
		lord->AddComponent(make_shared<BoxCollider>());
		AddGameObject(lord);
	}

	{

		shared_ptr<Lamp> lord = make_shared<Lamp>();

		shared_ptr<Model> model = Model::ReadData(L"lamp/lamp");
		lord->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		lord->SetTransform(transform);
		lord->_transform->SetLocalPosition(vec3(-45.0f, 0, 0));
		lord->_transform->SetLocalScale(vec3(0.05f, 0.05f, 0.05f));
		lord->_transform->SetLocalRotation(vec3(0, 90.0f, 0));
		AddGameObject(lord);
	}


	{

		shared_ptr<Lord> lord = make_shared<Lord>();

		shared_ptr<Model> model = Model::ReadData(L"road/road");
		lord->SetModel(model);

		shared_ptr<Transform> transform = make_shared<Transform>();
		lord->SetTransform(transform);
		AddGameObject(lord);
	}


	{

		for (int i = 0; i < 150; ++i)
		{
			int random = uid(dre);

			shared_ptr<Box> box = make_shared<Box>();

			shared_ptr<Model> model = Model::ReadData(L"box/box");
			box->SetModel(model);

			shared_ptr<Transform> transform = make_shared<Transform>();
			box->SetTransform(transform);
			if (random == 0)
			{
				box->_transform->SetLocalPosition(vec3(-60,0,uidZ(dre)));
			}
			else if (random == 1)
			{
				box->_transform->SetLocalPosition(vec3(-40, 0, uidZ(dre)));
			}
			else if (random == 2)
			{
				box->_transform->SetLocalPosition(vec3(-20, 0, uidZ(dre)));
			}
			else
			{
				box->_transform->SetLocalPosition(vec3(0, 0, uidZ(dre)));
			}

			box->_transform->SetLocalRotation(vec3(0, 180.0f, 0));

			box->AddComponent(make_shared<BoxCollider>());
			AddGameObject(box);
		}
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

	//충돌체 업데이트
	
}

void Stage1::Render()
{
	LightManager::GetInstnace()->SetData();
	Super::Render();
	CollisonManager::GetInstance()->Update();

}

void Stage1::ClearScene()
{
	Super::ClearScene();

	if (_sceneEnd)
	{
		SceneManger::GetInstance()->ChangeScene(SceneType::STARTSCENE);
	}

}


