#include "pch.h"
#include "..\Header\GameObject.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
}

CGameObject::~CGameObject()
{
	m_pDevice->Release();
}

void CGameObject::Update(const double& fDeltaTime)
{
	
}

void CGameObject::Render()
{

}