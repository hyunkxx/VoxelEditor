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
	// ���ؽ� ���� ���� �Լ�
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateVertexBuffer(
		m_nVtxSize * m_nVtxCnt, // ���� ������ ��ü ������(����Ʈ ����)
		0,					   // ���� ��� ���(0�� ���� ��� ���� ���۸� ���) -> D3DUSAGE_DYNAMIC�� �����ϴ� ��� ���� ����
		m_nFVF,				// ����ϴ� ���� ������ ��Ÿ���� �����ϴ� �÷���
		D3DPOOL_MANAGED,		// ���� ���� ��� �� �޸� Ǯ�� MANAGED, �������� ��� �� ������  D3DPOOL_DEFAULT�� ���
		&m_pVB,					// ��������� ���ؽ� ���� �İ�ü
		NULL)))					// ���� ���鶧 �ʿ��� ���� ����(NULL ������ ��)
		return E_FAIL;

	// ���ؽ� ���� ���� �Լ�
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateIndexBuffer(
		m_nIndexSize * m_nTriCnt, // �ε��� ������ ��ü ������(����Ʈ ����)
		0,					   // ���� ��� ���(0�� ���� ��� ���� ���۸� ���) -> D3DUSAGE_DYNAMIC�� �����ϴ� ��� ���� ����
		m_FMT,				// ����ϴ� ���� ������ ��Ÿ���� �����ϴ� �÷���
		D3DPOOL_MANAGED,		// ���� ���� ��� �� �޸� Ǯ�� MANAGED, �������� ��� �� ������  D3DPOOL_DEFAULT�� ���
		&m_pIB,					// ��������� ���ؽ� ���� �İ�ü
		NULL)))					// ���� ���鶧 �ʿ��� ���� ����(NULL ������ ��)
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer::Initalize(D3DCOLOR color)
{
	// ���ؽ� ���� ���� �Լ�
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateVertexBuffer(
		m_nVtxSize * m_nVtxCnt, // ���� ������ ��ü ������(����Ʈ ����)
		0,					   // ���� ��� ���(0�� ���� ��� ���� ���۸� ���) -> D3DUSAGE_DYNAMIC�� �����ϴ� ��� ���� ����
		m_nFVF,				// ����ϴ� ���� ������ ��Ÿ���� �����ϴ� �÷���
		D3DPOOL_MANAGED,		// ���� ���� ��� �� �޸� Ǯ�� MANAGED, �������� ��� �� ������  D3DPOOL_DEFAULT�� ���
		&m_pVB,					// ��������� ���ؽ� ���� �İ�ü
		NULL)))					// ���� ���鶧 �ʿ��� ���� ����(NULL ������ ��)
		return E_FAIL;

	// ���ؽ� ���� ���� �Լ�
	if (FAILED(CGraphic::GetInstance()->GetDevice()->CreateIndexBuffer(
		m_nIndexSize * m_nTriCnt, // �ε��� ������ ��ü ������(����Ʈ ����)
		0,					   // ���� ��� ���(0�� ���� ��� ���� ���۸� ���) -> D3DUSAGE_DYNAMIC�� �����ϴ� ��� ���� ����
		m_FMT,				// ����ϴ� ���� ������ ��Ÿ���� �����ϴ� �÷���
		D3DPOOL_MANAGED,		// ���� ���� ��� �� �޸� Ǯ�� MANAGED, �������� ��� �� ������  D3DPOOL_DEFAULT�� ���
		&m_pIB,					// ��������� ���ؽ� ���� �İ�ü
		NULL)))					// ���� ���鶧 �ʿ��� ���� ����(NULL ������ ��)
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Render()
{
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// SetStreamSource : ���ؽ� ������ ������ ����̽� ��ġ�� ��ũ��Ű�� �Լ�

	// 1. �� �� ����(��ġ�� �����͸� �����ϱ� ���� ������ ����)�� ������ ���ΰ�
	// 2. � ���� �Ѱ��� ���ΰ�
	// 3. ��𼭺��� �׸� ���ΰ�, 0�� ��� ������ ó������ �׸���
	// 4. � ������ ǥ���� ���ΰ�

	CGraphic::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, m_nVtxSize);

	// �� �����Ӹ��� ������ �Ӽ� ������ ����
	CGraphic::GetInstance()->GetDevice()->SetFVF(m_nFVF);

	// ����̽� ��ġ�� �ε��� ���۸� ��ũ
	CGraphic::GetInstance()->GetDevice()->SetIndices(m_pIB);

	// �׸��� �Լ�
	// 1. � ������ �׸� ���ΰ�
	// 2. 0�� ��� �� ��° ���ؽ����� �׸� ���ΰ�
	// 3. �� ���� ������ �׸� ���ΰ�
	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
	
	matrix matScale, matRotX, matRotY, matRotZ, matWorld, matView, matProj;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matWorld, 0.f, 0.f, 0.f);

	matWorld = matScale * matRotX * matRotY * matRotZ * matWorld;

	CGraphic::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVtxCnt, 0, m_nTriCnt);
}