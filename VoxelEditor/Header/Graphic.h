#pragma once
class CGraphic
{
	DECLARE_SINGLETON(CGraphic)
private:
	explicit CGraphic();
public:
	~CGraphic();
public:
	HRESULT Initalize(HWND hWnd, bool bWindowMode, CGraphic** ppGraphic);
	void	RenderBegin(D3DXCOLOR color);
	void	RenderEnd(HWND hWnd);

	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
private:
	LPDIRECT3D9				m_pSDK;
	LPDIRECT3DDEVICE9		m_pDevice;
};

