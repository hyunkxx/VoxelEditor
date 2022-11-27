#include "pch.h"
#include "..\Header\Triangle.h"

CTriangle::CTriangle()
{
}

CTriangle::~CTriangle()
{
}

HRESULT CTriangle::Initalize()
{
	m_nTriCnt	= 1;
	m_nVtxCnt	= 3;
	m_nVtxSize	= sizeof(Vertex);
	m_nFVF = FVF_TRI;

	m_nIndexSize = sizeof(Index32);
	m_FMT = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Initalize()))
		return E_FAIL;

	Vertex*	pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0); // 3인자 : 버텍스 버퍼의 원소 중 첫번째 주소 값을 추출

	pVertex[0].pos = { 0.f, 1.f, 0.f };
	pVertex[0].color = D3DXCOLOR{ 1.f, 1.f, 0.f , 1.f};

	pVertex[1].pos = { 1.f, -1.f, 0.f };
	pVertex[1].color = D3DXCOLOR{ 1.f, 1.f, 0.f, 1.f};

	pVertex[2].pos = { -1.f, -1.f, 0.f };
	pVertex[2].color = D3DXCOLOR{ 1.f, 1.f, 0.f, 1.f};

	m_pVB->Unlock();

	Index32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	m_pIB->Unlock();

	return S_OK;
}
