#include "pch.h"
#include "..\Header\Camera.h"

#include "Core.h"
#include "Cube.h"
#include "Graphic.h"
#include "CubeManager.h"

/* 생성 초기 값 */
float CCubeManager::fScale[3] = { 1.f,1.f,1.f };
float CCubeManager::fRotation[3] = { 0.f,0.f,0.f };
float CCubeManager::fPos[3] = { 0.f,0.f,0.f };

CCamera::CCamera(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
	, m_fDistance(0.f)
	, m_fMoveSpeed(10.f)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	m_fFOV = D3DXToRadian(60.f);

	ZeroMemory(&CameraState, sizeof(CameraState));
}


CCamera::~CCamera()
{
}

void CCamera::OhtoCamera()
{
	D3DXMatrixOrthoLH(&m_matProj, WIN_WIDTH/40 , WIN_HEIGHT/40, -1.f, 1000.f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CCamera::SetupCamera(const vec3& vPos, const vec3& vAt)
{
	m_vPos = vPos;
	m_vAt = vAt;

	D3DXMatrixLookAtLH(&m_matView, &vPos, &vAt, &vUP);
	m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFOV, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CCamera::TransformSetting()
{

}

bool CCamera::ChangeView()
{
	matrix view;
	D3DXMatrixIdentity(&view);
	//정면
	if (ImGui::GetIO().KeysDown[VK_F1])
	{
		ZeroMemory(&(CCubeManager::GetInstance()->m_rotAngle),sizeof(Rotation));
		D3DXMatrixLookAtLH(&view, new vec3{ 0.f,0.f,100.f }, new vec3{0.f,0.f,0.f}, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &view);
		CameraState[(UINT)VIEW::FORWARD] = true;
		return true;
	}
	//후면
	else if (ImGui::GetIO().KeysDown[VK_F2])
	{
		ZeroMemory(&(CCubeManager::GetInstance()->m_rotAngle), sizeof(Rotation));
		D3DXMatrixLookAtLH(&view, new vec3{ 0.f,0.f,-100.f }, new vec3{ 0.f,0.f,0.f }, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &view);
		CameraState[(UINT)VIEW::BACKWARD] = true;
		return true;
	}
	//우측
	else if (ImGui::GetIO().KeysDown[VK_F3])
	{
		ZeroMemory(&(CCubeManager::GetInstance()->m_rotAngle), sizeof(Rotation));
		D3DXMatrixLookAtLH(&view, new vec3{ 100.f,0.f,0.f }, new vec3{ 0.f,0.f,0.f }, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &view);
		CameraState[(UINT)VIEW::RIGHT] = true;
		return true;
	}
	//좌측
	else if (ImGui::GetIO().KeysDown[VK_F4])
	{
		ZeroMemory(&(CCubeManager::GetInstance()->m_rotAngle), sizeof(Rotation));
		D3DXMatrixLookAtLH(&view, new vec3{ -100.f,0.f,0.f }, new vec3{ 0.f,0.f,0.f }, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &view);
		CameraState[(UINT)VIEW::LEFT] = true;
		return true;
	}
	else if (ImGui::GetIO().KeysDown[VK_F5])
	{
		ZeroMemory(&(CCubeManager::GetInstance()->m_rotAngle), sizeof(Rotation));
		D3DXMatrixLookAtLH(&view, new vec3{ 0.f,100.f,0.f }, new vec3{ -1.f,0.f,0.f }, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &view);
		CameraState[(UINT)VIEW::UP] = true;
		return true;
	}
	else if (ImGui::GetIO().KeysDown[VK_F6])
	{
		ZeroMemory(&(CCubeManager::GetInstance()->m_rotAngle), sizeof(Rotation));
		D3DXMatrixLookAtLH(&view, new vec3{ 0.f,-100.f,0.f }, new vec3{ -1.f,0.f,0.f }, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &view);
		CameraState[(UINT)VIEW::DOWN] = true;
		return true;
	}
	return false;
}

void CCamera::Zoom()
{
	if (g_bWheelUpdate)
	{
		vec3 vDir = m_vAt - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		m_fDistance = g_nZoom;
		vec3 vLength = vDir * m_fDistance;

		m_vPos += vLength;
		m_vAt  += vLength;

		g_nZoom = 0.f;
		g_bWheelUpdate = false;
	}
}

//WASD 카메라 이동
void CCamera::Movement()
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		vec3 vDir = m_vAt - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		m_fDistance = g_nZoom;

		vec3 vLength = vDir * m_fMoveSpeed * DT;

		m_vPos += vLength;
		m_vAt  += vLength;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		vec3 vDir = m_vAt - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		m_fDistance = g_nZoom;

		vec3 vLength = -vDir * m_fMoveSpeed * DT;

		m_vPos += vLength;
		m_vAt  += vLength;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		vec3 vRight = { m_matView._11, m_matView._12, m_matView._13 };
		D3DXVec3Normalize(&vRight, &vRight);

		m_fDistance = g_nZoom;

		vec3 vLength = vRight * m_fMoveSpeed * DT;

		m_vPos += vLength;
		m_vAt  += vLength;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		vec3 vRight = { m_matView._11, m_matView._12, m_matView._13 };
		D3DXVec3Normalize(&vRight, &vRight);

		m_fDistance = g_nZoom;

		vec3 vLength = -vRight * m_fMoveSpeed * DT;

		m_vPos += vLength;
		m_vAt  += vLength;
	}
}
//회전
void CCamera::KeyRotation()
{
	if (GetAsyncKeyState('E') & 0x8000)
		CCubeManager::GetInstance()->m_rotAngle.y += 90.f * DT;

	if (GetAsyncKeyState('Q') & 0x8000)
		CCubeManager::GetInstance()->m_rotAngle.y -= 90.f * DT;

	if (GetAsyncKeyState('F') & 0x8000)
		CCubeManager::GetInstance()->m_rotAngle.x += 90.f * DT;

	if (GetAsyncKeyState('R') & 0x8000)
		CCubeManager::GetInstance()->m_rotAngle.x -= 90.f * DT;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		CCubeManager::GetInstance()->ResetAngle();
		m_vPos	= { 0.f, 10.f, -20.f };
		m_vAt	= { 0.f,0.f,0.f };
	}
}

void CCamera::MouseRotation()
{
	//vec3 camRotation;
	//ZeroMemory(&camRotation, sizeof(vec3));

	//vLook = m_vAt - m_vPos;

	//matrix	matCamWorld;
	//D3DXMatrixInverse(&matCamWorld, nullptr, &m_matView);
	//memcpy(&vRight, &matCamWorld.m[0][0], sizeof(vec3));
	//memcpy(&vUp,	&matCamWorld.m[1][1], sizeof(vec3));

	//ImVec2 mouseDelta = ImGui::GetMouseDragDelta();
	//
	//matrix matRot;
	//D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(ImGui::GetIO().MouseDelta.y));
	//D3DXMatrixRotationAxis(&matRot, &vUp,	 D3DXToRadian(ImGui::GetIO().MouseDelta.x));

	//D3DXVec3TransformNormal(&vLook, &vLook, &matRot);
	//m_vAt = m_vPos + vLook;

	//m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCamera::Initalize()
{
}

void CCamera::Update(const double& fDeltaTime)
{
	Zoom();

	Movement();
	KeyRotation();

	if (!ChangeView())
	{
		D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vAt, &vUP);
		m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

		D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFOV, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.f);
		m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	}
	else
	{
		D3DXMatrixOrthoLH(&m_matProj, 10, 10, 0.f, 100.f);
		m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	}
}

void CCamera::Render()
{
}

void CCamera::RenderUI()
{
	string mouseDistance = to_string(m_fDistance);
	string Zoom = to_string(g_nZoom);

	string cameraX = to_string(m_vPos.x);
	string cameraY = to_string(m_vPos.y);
	string cameraZ = to_string(m_vPos.z);

	ImGui::SetWindowSize(ImVec2(0, 500));
	ImGui::SetWindowPos(ImVec2(100, 500));
	ImGui::Begin("Editor Log",0 , ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("mouse zoom delta");
	ImGui::SameLine();
	ImGui::Text(mouseDistance.c_str());
	ImGui::SameLine();
	ImGui::Text(Zoom.c_str());

	ImGui::Text("camera position ");
	ImGui::SameLine();
	ImGui::Text(cameraX.c_str());
	ImGui::SameLine();
	ImGui::Text(cameraY.c_str());
	ImGui::SameLine();
	ImGui::Text(cameraZ.c_str());

	string rotX = to_string(CCubeManager::GetInstance()->m_rotAngle.x);
	string rotY = to_string(CCubeManager::GetInstance()->m_rotAngle.y);
	string rotZ = to_string(CCubeManager::GetInstance()->m_rotAngle.z);

	ImGui::Text("object angle    ");
	ImGui::SameLine();
	ImGui::Text(rotX.c_str());
	ImGui::SameLine();
	ImGui::Text(rotY.c_str());
	ImGui::SameLine();
	ImGui::Text(rotZ.c_str());

	ImGui::End();
}
