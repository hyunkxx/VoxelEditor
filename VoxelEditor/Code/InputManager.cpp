#include "pch.h"
#include "..\Header\InputManager.h"

#include "Cube.h"
#include "CubeManager.h"
#include "SaveLoader.h"


CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}

void CInputManager::KeyInput()
{
	ColorPickChange();
	KeyObjectMove();
	SaveLoadCheck();
	ObjectClone();
	DeleteCube();
}

void CInputManager::SaveLoadCheck()
{
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000 && GetAsyncKeyState('S') & 0x8000)
		CSaveLoader::SaveFile();
}

void CInputManager::DeleteCube()
{
	if (GetAsyncKeyState(VK_DELETE) & 0x8000)
	{
		CCubeManager::GetInstance()->DeleteCube();
	}
}

void CInputManager::MouseLeftButton()
{
	if (ImGui::GetIO().MouseClicked[ImGuiMouseButton_Left] && ImGui::GetIO().MousePos.x <= WIN_WIDTH - IMGUI_INSPECTOR_WIDTH)
		CCubeManager::GetInstance()->Pick();
}

void CInputManager::KeyObjectMove()
{
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_RightArrow, false))
	{
		CCube* pCube = CCubeManager::GetInstance()->GetSeletedObject();
		if (pCube)
			pCube->m_vPos.x += .1f;
	}
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_LeftArrow, false))
	{
		CCube* pCube = CCubeManager::GetInstance()->GetSeletedObject();
		if (pCube)
			pCube->m_vPos.x -= .1f;
	}
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_UpArrow, false))
	{
		CCube* pCube = CCubeManager::GetInstance()->GetSeletedObject();
		if (pCube)
			pCube->m_vPos.z += .1f;
	}
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_DownArrow, false))
	{
		CCube* pCube = CCubeManager::GetInstance()->GetSeletedObject();
		if (pCube)
			pCube->m_vPos.z -= .1f;
	}

	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_PageUp, false))
	{
		CCube* pCube = CCubeManager::GetInstance()->GetSeletedObject();
		if (pCube)
			pCube->m_vPos.y += .1f;
	}
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_PageDown, false))
	{
		CCube* pCube = CCubeManager::GetInstance()->GetSeletedObject();
		if (pCube)
			pCube->m_vPos.y -= .1f;
	}
}

void CInputManager::ColorPickChange()
{
	if (ImGui::GetIO().MouseClicked[ImGuiMouseButton_Left] && ImGui::GetIO().MousePos.x <= WIN_WIDTH - IMGUI_INSPECTOR_WIDTH)
	{
		if (CCubeManager::GetInstance()->Pick())
		{
			CCubeManager::GetInstance()->curColor	 = CCubeManager::GetInstance()->GetSeletedObject()->dwColor;
			CCubeManager::GetInstance()->m_tempScale = CCubeManager::GetInstance()->GetSeletedObject()->m_vScale;
			memcpy(&CCubeManager::GetInstance()->m_tempRotation, &CCubeManager::GetInstance()->GetSeletedObject()->m_Angle, sizeof(Rotation));
		}
	}

	if (ImGui::GetIO().MouseClicked[ImGuiMouseButton_Right] && ImGui::GetIO().MousePos.x <= WIN_WIDTH - IMGUI_INSPECTOR_WIDTH)
	{
		if (CCubeManager::GetInstance()->Pick())
		{
			CCubeManager::GetInstance()->GetSeletedObject()->dwColor = CCubeManager::GetInstance()->curColor;
			CCubeManager::GetInstance()->GetSeletedObject()->ApplyColor();
		}
	}
}

void CInputManager::ObjectClone()
{
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_F12) && ImGui::GetIO().MousePos.x <= WIN_WIDTH - IMGUI_INSPECTOR_WIDTH)
	{
		if (CCubeManager::GetInstance()->Pick())
		{
			CCubeManager::GetInstance()->GetSeletedObject()->m_vScale = CCubeManager::GetInstance()->m_tempScale;
			memcpy(&CCubeManager::GetInstance()->GetSeletedObject()->m_Angle, &CCubeManager::GetInstance()->m_tempRotation, sizeof(Rotation));
		}
	}
}
