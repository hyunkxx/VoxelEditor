#include "pch.h"
#include "..\Header\ImguiManager.h"

#include "Graphic.h"
#include "SaveLoader.h"

IMPLEMENT_SINGLETON(ImguiManager)

ImguiManager::ImguiManager()
{
}

ImguiManager::~ImguiManager()
{
	Showdown();
}

void ImguiManager::Initalize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	// Setup Platform/Renderer backends

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(CGraphic::GetInstance()->GetDevice());
}

void ImguiManager::NewFrame()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	{		
		ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - IMGUI_INSPECTOR_WIDTH - 210, 20));
		ImGui::SetNextWindowSize(ImVec2(210, 20));
		ImGui::Begin("Frame", nullptr , ImGuiWindowFlags_NoBackground |ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		ImGui::SameLine();
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

void ImguiManager::Render()
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::EndFrame()
{
	ImGui::EndFrame();

	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
}

void ImguiManager::Showdown()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::DrawMainMenuBar()
{
	static bool bSave = false;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("file"))
		{
			if (ImGui::MenuItem("save as filename"))
			{
				CSaveLoader::SaveFile();
			}

			if (ImGui::MenuItem("load head mesh"))
			{
				CSaveLoader::LoadFile(CUBE_TYPE::HEAD);
			}

			if (ImGui::MenuItem("load body mesh"))
			{
				CSaveLoader::LoadFile(CUBE_TYPE::BODY);
			}
			if (ImGui::MenuItem("load object mesh"))
			{
				CSaveLoader::LoadFile(CUBE_TYPE::OBJECT);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}