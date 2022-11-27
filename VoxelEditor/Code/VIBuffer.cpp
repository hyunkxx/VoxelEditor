#include "pch.h"
#include "..\Header\VIBuffer.h"

#include "Graphic.h"

CVIBuffer::CVIBuffer()
	: m_pVB(nullptr)
	, m_pIB(nullptr)
	, m_nVtxSize(0)
	, m_nTriCnt(0)
	, m_nFVF(0)
	, m_nVtxCnt(0)
	, m_nIndexSize(0)
{
}


CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Initalize()
{
	// 버텍스 버퍼 생성 함수
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateVertexBuffer(
		m_nVtxSize * m_nVtxCnt, // 정점 버퍼의 전체 사이즈(바이트 단위)
		0,					   // 버퍼 사용 방식(0을 넣을 경우 정적 버퍼를 사용) -> D3DUSAGE_DYNAMIC을 지정하는 경우 동적 버퍼
		m_nFVF,				// 사용하는 정점 버퍼의 스타일을 지정하는 플래그
		D3DPOOL_MANAGED,		// 정적 버퍼 사용 시 메모리 풀은 MANAGED, 동적버퍼 사용 시 무조건  D3DPOOL_DEFAULT를 사용
		&m_pVB,					// 만들어지는 버텍스 버퍼 컴객체
		NULL)))					// 버퍼 만들때 필요한 예약 상태(NULL 넣으면 됨)
		return E_FAIL;

	// 버텍스 버퍼 생성 함수
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateIndexBuffer(
		m_nIndexSize * m_nTriCnt, // 인덱스 버퍼의 전체 사이즈(바이트 단위)
		0,					   // 버퍼 사용 방식(0을 넣을 경우 정적 버퍼를 사용) -> D3DUSAGE_DYNAMIC을 지정하는 경우 동적 버퍼
		m_FMT,				// 사용하는 정점 버퍼의 스타일을 지정하는 플래그
		D3DPOOL_MANAGED,		// 정적 버퍼 사용 시 메모리 풀은 MANAGED, 동적버퍼 사용 시 무조건  D3DPOOL_DEFAULT를 사용
		&m_pIB,					// 만들어지는 버텍스 버퍼 컴객체
		NULL)))					// 버퍼 만들때 필요한 예약 상태(NULL 넣으면 됨)
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer::Initalize(D3DCOLOR color)
{
	// 버텍스 버퍼 생성 함수
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateVertexBuffer(
		m_nVtxSize * m_nVtxCnt, // 정점 버퍼의 전체 사이즈(바이트 단위)
		0,					   // 버퍼 사용 방식(0을 넣을 경우 정적 버퍼를 사용) -> D3DUSAGE_DYNAMIC을 지정하는 경우 동적 버퍼
		m_nFVF,				// 사용하는 정점 버퍼의 스타일을 지정하는 플래그
		D3DPOOL_MANAGED,		// 정적 버퍼 사용 시 메모리 풀은 MANAGED, 동적버퍼 사용 시 무조건  D3DPOOL_DEFAULT를 사용
		&m_pVB,					// 만들어지는 버텍스 버퍼 컴객체
		NULL)))					// 버퍼 만들때 필요한 예약 상태(NULL 넣으면 됨)
		return E_FAIL;

	// 버텍스 버퍼 생성 함수
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateIndexBuffer(
		m_nIndexSize * m_nTriCnt, // 인덱스 버퍼의 전체 사이즈(바이트 단위)
		0,					   // 버퍼 사용 방식(0을 넣을 경우 정적 버퍼를 사용) -> D3DUSAGE_DYNAMIC을 지정하는 경우 동적 버퍼
		m_FMT,				// 사용하는 정점 버퍼의 스타일을 지정하는 플래그
		D3DPOOL_MANAGED,		// 정적 버퍼 사용 시 메모리 풀은 MANAGED, 동적버퍼 사용 시 무조건  D3DPOOL_DEFAULT를 사용
		&m_pIB,					// 만들어지는 버텍스 버퍼 컴객체
		NULL)))					// 버퍼 만들때 필요한 예약 상태(NULL 넣으면 됨)
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Render()
{
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// SetStreamSource : 버텍스 버퍼의 내용을 디바이스 장치와 링크시키는 함수

	// 1. 몇 번 슬롯(장치는 데이터를 보관하기 위한 슬롯이 존재)에 보관할 것인가
	// 2. 어떤 것을 넘겨줄 것인가
	// 3. 어디서부터 그릴 것인가, 0인 경우 버퍼의 처음부터 그리기
	// 4. 어떤 단위로 표현할 것인가

	CGraphic::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, m_nVtxSize);

	// 매 프레임마다 정점의 속성 정보를 갱신
	CGraphic::GetInstance()->GetDevice()->SetFVF(m_nFVF);

	// 디바이스 장치와 인덱스 버퍼를 링크
	CGraphic::GetInstance()->GetDevice()->SetIndices(m_pIB);

	// 그리기 함수
	// 1. 어떤 도형을 그릴 것인가
	// 2. 0인 경우 몇 번째 버텍스부터 그릴 것인가
	// 3. 몇 개의 도형을 그릴 것인가
	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
	
	matrix matScale, matRotX, matRotY, matRotZ, matWorld, matView, matProj;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matWorld, 0.f, 0.f, 0.f);

	matWorld = matScale * matRotX * matRotY * matRotZ * matWorld;

	CGraphic::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVtxCnt, 0, m_nTriCnt);
}