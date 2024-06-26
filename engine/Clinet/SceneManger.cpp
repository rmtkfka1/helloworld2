#include "pch.h"
#include "SceneManger.h"
#include "Scene.h"
#include "Stage1.h"
#include "StartScene.h"

void SceneManger::Init()
{
	if (_scene)
		_scene->Init();

}

void SceneManger::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManger::LateUpdate()
{
	if (_scene)
		_scene->LateUpdate();
}


void SceneManger::Render()
{
	if (_scene)
		_scene->Render();
}

void SceneManger::ClearScene()
{
	if (_scene)
		_scene->ClearScene();
}

void SceneManger::ChangeScene(SceneType type)
{

	if (_sceneType == type)
		return;


	switch (type)
	{
	case SceneType::STAGE1:
		_scene = make_shared<Stage1>();
		break;
	case SceneType::STARTSCENE:
		_scene = make_shared<StartScene>();
		break;

	default:
		break;
	}

	_sceneType = type;
	_scene->Init();
}


