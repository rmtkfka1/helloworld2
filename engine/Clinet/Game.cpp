#include "pch.h"
#include "Game.h"
#include "Core.h"
#include "Shader.h"
#include "Mesh.h"
#include "ImguiManager.h"
#include "Texture.h"
#include "SceneManger.h"



void Game::Init(WindowInfo info)
{
	_info = info;

	core->Init(_info);
	SceneManger::GetInstance()->ChangeScene(SceneType::STARTSCENE);

}

void Game::Run()
{
	core->Update();
	core->StartRender();
	SceneManger::GetInstance()->Update();
	SceneManger::GetInstance()->LateUpdate();
	SceneManger::GetInstance()->Render();
	core->EndRender();
	SceneManger::GetInstance()->ClearScene();
}
