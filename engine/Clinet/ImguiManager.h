#pragma once
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_impl_dx12.h"

class ImguiManager
{

public:

	static ImguiManager* GetInstance()
	{
		static ImguiManager instance;
		return &instance;

	};


	~ImguiManager();


	void Init();
	void Render();

public:
	static int ObjectCount;
	static int playerHp;
	static int testing;



private:
	bool show_demo_window = false;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

