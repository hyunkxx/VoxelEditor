#pragma once

class CGraphic;
class CGameObject;
class CCubeManager;
class CCamera;

class CCore
{
	DECLARE_SINGLETON(CCore)
public:
	explicit CCore();
	~CCore();
public:
	HRESULT Initalize();
	void	Update();
	void	Render();
	void	Release();
private:
	void SetRenderState();
public:
	CGameObject* GetCamera() { return m_pCamera; }
private:
	void UIFrame();
	void SettingDeltaTime();
public:
	float fDeltaTime;
private:
	/* Device */
	CGraphic* m_pGraphic;
	
	/* Object */
	CGameObject* m_pCamera;
	CGameObject* m_pAxis;

	/* DeltaTime Counter */
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER Frequency;
	double timeScale;
};
