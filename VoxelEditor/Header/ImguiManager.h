#pragma once
class ImguiManager
{
	DECLARE_SINGLETON(ImguiManager)
public:
	ImguiManager();
	~ImguiManager();
public:
	void Initalize();
	void NewFrame();
	void Render();
	void EndFrame();
	void Showdown();
public:
	void DrawMainMenuBar();
};

