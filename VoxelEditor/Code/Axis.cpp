#include "pch.h"
#include "..\Header\Axis.h"
#include "Cube.h"

#include "Core.h"
#include "Graphic.h"
#include "CubeManager.h"
#include "Camera.h"

CAxis::CAxis(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
	D3DXMatrixIdentity(&m_matWorld);

	m_pAxis[(uint32)Axis::X] = new CCube(CUBE_TYPE::END, vec3(1.f, 0.05f, 0.05f), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f));
	m_pAxis[(uint32)Axis::Y] = new CCube(CUBE_TYPE::END, vec3(0.05f, 1.f, 0.05f), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f));
	m_pAxis[(uint32)Axis::Z] = new CCube(CUBE_TYPE::END, vec3(0.05f, 0.05f, 1.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f));


	if (FAILED(m_pAxis[(uint32)Axis::X]->Initalize(D3DCOLOR_RGBA(255,0,0,255))))
	{
		SafeDelete(m_pAxis[(uint32)Axis::X]);
		MSG_BOX("Failed Create Cube!");
	}
	if (FAILED(m_pAxis[(uint32)Axis::Y]->Initalize(D3DCOLOR_RGBA(0, 255, 0, 255))))
	{
		SafeDelete(m_pAxis[(uint32)Axis::Y]);
		MSG_BOX("Failed Create Cube!");
	}
	if (FAILED(m_pAxis[(uint32)Axis::Z]->Initalize(D3DCOLOR_RGBA(0, 0, 255, 255))))
	{
		SafeDelete(m_pAxis[(uint32)Axis::Z]);
		MSG_BOX("Failed Create Cube!");
	}
}

CAxis::~CAxis()
{
	for (int i = 0; i < 3; ++i)
	{
		delete m_pAxis[i];
	}
}

void CAxis::Initalize()
{
}

void CAxis::Update(const double & fDeltaTime)
{
}

void CAxis::Render()
{
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	CCamera* pCamera = static_cast<CCamera*>(CCore::GetInstance()->GetCamera());
	vec3 vCamPos = pCamera->GetPosition();
	vec3 vCamDir = pCamera->GetDirection();

	static vec3 origin   = { 0.f, 0.f, 0.f };
	static vec3 up		 = { 1.f, 0.f, 0.f };
	static vec3 right	 = { 0.f, 1.f, 0.f };
	static vec3 front	 = { 0.f, 0.f, 1.f };


	vCamPos += vCamDir * 1.f;
	for (size_t i = 0; i < (uint32)Axis::END; ++i)
	{
		matrix matScale, matTrans, matRotation, matPRotation;
		matrix matRot[3];

		D3DXMatrixIdentity(&matTrans);
		D3DXMatrixIdentity(&matRotation);
		D3DXMatrixIdentity(&matPRotation);

		D3DXMatrixScaling(&matScale, m_pAxis[i]->m_vScale.x, m_pAxis[i]->m_vScale.y, m_pAxis[i]->m_vScale.z);
		
		D3DXMatrixRotationX(&matRot[0], D3DXToRadian(CCubeManager::GetInstance()->GetAngle().x));
		D3DXMatrixRotationY(&matRot[1], D3DXToRadian(CCubeManager::GetInstance()->GetAngle().y));
		D3DXMatrixRotationZ(&matRot[2], D3DXToRadian(CCubeManager::GetInstance()->GetAngle().z));

		vec3 camDir = pCamera->GetDirection();

		matRotation = matRot[0] * matRot[1] * matRot[2];

		D3DXMatrixTranslation(&matTrans, -13.f, +10, 1);

		m_pAxis[i]->m_matWorld = matScale * matRotation * matTrans;
		CGraphic::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_pAxis[i]->m_matWorld);
		
		matrix mat;
		D3DXMatrixIdentity(&mat);
		m_pDevice->SetTransform(D3DTS_VIEW, &mat);

		pCamera->OhtoCamera();
		m_pAxis[i]->Render();
	}
	pCamera->SetupCamera(pCamera->GetPosition(), pCamera->GetLookAt());
}

void CAxis::RenderUI()
{
}
