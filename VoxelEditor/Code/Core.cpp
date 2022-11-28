#include "pch.h"
#include "..\Header\Core.h"

#include "Graphic.h"
#include "ImguiManager.h"

#include "Triangle.h"
#include "Cube.h"

#include "Axis.h"
#include "GameObject.h"
#include "Camera.h"

#include "CubeManager.h"
#include "SaveLoader.h"
#include "InputManager.h"

IMPLEMENT_SINGLETON(CCore)

CCore::CCore()
	: m_pGraphic(nullptr)
	, m_pCamera(nullptr)
{
	Initalize();
	QueryPerformanceFrequency(&Frequency);
	timeScale = 1.0f / (double)Frequency.QuadPart; 

	QueryPerformanceCounter(&beginTime);
}

CCore::~CCore()
{
	Release();
}

HRESULT CCore::Initalize()
{
	HRESULT result = CGraphic::GetInstance()->Initalize(g_hWnd, true, &m_pGraphic);

	SetRenderState();

	/* Camera Setting */
	m_pAxis = new CAxis(m_pGraphic->GetDevice());
	m_pCamera = new CCamera(m_pGraphic->GetDevice());
	static_cast<CCamera*>(m_pCamera)->SetupCamera({ 0.f, 10.f, -20.f }, { 0.f,0.f,0.f });
	CCubeManager::GetInstance()->CreateCube(CUBE_TYPE::BODY, { 1.f,0.5f,2.f }, vec3{ 0.f,0.f,0.f }, {0.f,0.f,0.f}, D3DCOLOR_RGBA(255,255,255,255));
	CCubeManager::GetInstance()->CreateCube(CUBE_TYPE::BODY, { 0.2f,0.5f,2.f }, vec3{ 0.f,0.f,0.f }, { -1.2f,-0.4f,0.f }, D3DCOLOR_RGBA(255, 255, 255, 255));
	CCubeManager::GetInstance()->CreateCube(CUBE_TYPE::BODY, { 0.2f,0.5f,2.f }, vec3{ 0.f,0.f,0.f }, {  1.2f,-0.4f,0.f }, D3DCOLOR_RGBA(255, 255, 255, 255));
	return result;
}

void CCore::Update()
{
	SettingDeltaTime();

	m_pCamera->Update(fDeltaTime);
	CInputManager::KeyInput();
}

void CCore::Render()
{
	UIFrame();
	
	m_pGraphic->RenderBegin({0.5f,0.5f,0.5f,1.f});
	CCubeManager::GetInstance()->Render();
	m_pAxis->Render();
	ImguiManager::GetInstance()->Render();
	m_pGraphic->RenderEnd(g_hWnd);
}

void CCore::Release()
{
	delete m_pAxis;
	delete m_pCamera;

	CCubeManager::DestroyInstance();
	ImguiManager::DestroyInstance();
	CGraphic::DestroyInstance();
}

void CCore::SetRenderState()
{
	m_pGraphic->GetDevice()->SetPixelShader(NULL);
	m_pGraphic->GetDevice()->SetVertexShader(NULL);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_ZENABLE, false);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_pGraphic->GetDevice()->SetRenderState(D3DRS_FOGENABLE, false);
	m_pGraphic->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pGraphic->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pGraphic->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pGraphic->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pGraphic->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pGraphic->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pGraphic->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphic->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

void CCore::UIFrame()
{
	ImguiManager::GetInstance()->NewFrame();
	m_pCamera->RenderUI();
	CCubeManager::GetInstance()->RenderIndex();
	CCubeManager::GetInstance()->RenderUI();


	CSaveLoader::RenderGUI();

	ImguiManager::GetInstance()->DrawMainMenuBar();
	ImguiManager::GetInstance()->EndFrame();
}

void CCore::SettingDeltaTime()
{
	QueryPerformanceCounter(&endTime);
	fDeltaTime = (float)(endTime.QuadPart - beginTime.QuadPart) / (float)Frequency.QuadPart;
	QueryPerformanceCounter(&beginTime);
}
