#pragma once
class CVIBuffer
{
public:
	explicit CVIBuffer();
	virtual ~CVIBuffer();
public:
	virtual HRESULT Initalize();
	virtual HRESULT Initalize(D3DCOLOR color);

	virtual void	Render();
	
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() { return m_pVB; }
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
protected:
	uint32		m_nVtxCnt;
	uint32		m_nVtxSize;
	uint32		m_nTriCnt;
	uint32		m_nFVF;

	uint32		m_nIndexSize;
	D3DFORMAT	m_FMT;
};

