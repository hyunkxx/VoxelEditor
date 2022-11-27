#pragma once
class CGameObject
{
public:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CGameObject();
public:
	virtual void Initalize() PURE;
	virtual void Update(const double& fDeltaTime) PURE;
	virtual void Render() PURE;
	virtual void RenderUI() PURE;
protected:
	LPDIRECT3DDEVICE9 m_pDevice;
};

