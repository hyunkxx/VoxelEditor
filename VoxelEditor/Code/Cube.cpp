#include "pch.h"
#include "..\Header\Cube.h"

int32 CCube::s_nID = 0;

CCube::CCube()
	: m_vScale(1.f,1.f,1.f)
	, m_Angle({ 0.f,0.f,0.f })
	, m_vPos(0.f,0.f,0.f)
	, m_eType(CUBE_TYPE::END)
{
	m_nIndex = s_nID++;
	D3DXMatrixIdentity(&m_matWorld);
}

CCube::CCube(CUBE_TYPE eType,vec3 vScale, Rotation tagAngle, vec3 vPos)
	: m_vScale(vScale)
	, m_Angle(tagAngle)
	, m_vPos(vPos)
	, m_eType(eType)
{
	m_nIndex = s_nID++;
	D3DXMatrixIdentity(&m_matWorld);
}

CCube::~CCube()
{
}

HRESULT CCube::Initalize()
{
	m_nVtxCnt = 8;
	m_nVtxSize = sizeof(Vertex);
	m_nTriCnt = 12;
	m_nFVF = FVF_CUBE;
	  
	m_nIndexSize = sizeof(Index32);
	m_FMT = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Initalize()))
		return E_FAIL;

	Vertex*	pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0); // 3인자 : 버텍스 버퍼의 원소 중 첫번째 주소 값을 추출

	dwColor = D3DCOLOR_RGBA(255, 0, 0, 255);

	pVertex[0].pos = { -1.f, 1.f, -1.f };
	pVertex[0].color = D3DCOLOR_RGBA(255, 0, 0, 255);
			   
	pVertex[1].pos = { 1.f, 1.f,-1.f };
	pVertex[1].color = D3DCOLOR_RGBA(0, 255, 0, 255);

	pVertex[2].pos = { 1.f, -1.f, -1.f };
	pVertex[2].color = D3DCOLOR_RGBA(0, 0, 255, 255);

	pVertex[3].pos = { -1.f, -1.f, -1.f };
	pVertex[3].color = D3DCOLOR_RGBA(255, 0, 0, 255);

	pVertex[4].pos = { -1.f, 1.f, 1.f };
	pVertex[4].color = D3DCOLOR_RGBA(0, 255, 0, 255);

	pVertex[5].pos = { 1.f, 1.f, 1.f };
	pVertex[5].color = D3DCOLOR_RGBA(0, 0, 255, 255);

	pVertex[6].pos = { 1.f, -1.f, 1.f };
	pVertex[6].color = D3DCOLOR_RGBA(255, 0, 0, 255);

	pVertex[7].pos = { -1.f, -1.f, 1.f };
	pVertex[7].color = D3DCOLOR_RGBA(0, 255, 0, 255);

	m_pVB->Unlock();

	Index32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	// y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	
	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CCube::Initalize(D3DCOLOR color)
{
	m_nVtxCnt = 8;
	m_nVtxSize = sizeof(Vertex);
	m_nTriCnt = 12;
	m_nFVF = FVF_CUBE;

	m_nIndexSize = sizeof(Index32);
	m_FMT = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Initalize(color)))
		return E_FAIL;

	Vertex*	pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0); // 3인자 : 버텍스 버퍼의 원소 중 첫번째 주소 값을 추출
											// 위쪽 
	dwColor = color;

	pVertex[0].pos = { -1.f, 1.f, -1.f };
	pVertex[0].color = color;

	pVertex[1].pos = { 1.f, 1.f,-1.f };
	pVertex[1].color = color;

	pVertex[2].pos = { 1.f, -1.f, -1.f };
	pVertex[2].color = color;

	pVertex[3].pos = { -1.f, -1.f, -1.f };
	pVertex[3].color = color;

	pVertex[4].pos = { -1.f, 1.f, 1.f };
	pVertex[4].color = color;

	pVertex[5].pos = { 1.f, 1.f, 1.f };
	pVertex[5].color = color;

	pVertex[6].pos = { 1.f, -1.f, 1.f };
	pVertex[6].color = color;

	pVertex[7].pos = { -1.f, -1.f, 1.f };
	pVertex[7].color = color;

	m_pVB->Unlock();

	Index32* pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	// y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;


	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CCube::RenderIndex()
{

}

void CCube::ApplyColor()
{
	Vertex*	pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
											
	pVertex[0].pos = { -1.f, 1.f, -1.f };
	pVertex[0].color = dwColor;

	pVertex[1].pos = { 1.f, 1.f,-1.f };
	pVertex[1].color = dwColor;

	pVertex[2].pos = { 1.f, -1.f, -1.f };
	pVertex[2].color = dwColor;

	pVertex[3].pos = { -1.f, -1.f, -1.f };
	pVertex[3].color = dwColor;

	pVertex[4].pos = { -1.f, 1.f, 1.f };
	pVertex[4].color = dwColor;

	pVertex[5].pos = { 1.f, 1.f, 1.f };
	pVertex[5].color = dwColor;

	pVertex[6].pos = { 1.f, -1.f, 1.f };
	pVertex[6].color = dwColor;

	pVertex[7].pos = { -1.f, -1.f, 1.f };
	pVertex[7].color = dwColor;

	m_pVB->Unlock();
}


