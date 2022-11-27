#pragma once

#include "GameObject.h"

class CCube;
class CAxis : public CGameObject
{
public:
	enum class Axis { X, Y, Z, END };
public:
	explicit CAxis(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CAxis();
public:
	virtual void Initalize() override;
	virtual void Update(const double& fDeltaTime) override;
	virtual void Render() override;
	virtual void RenderUI() override;
private:
	matrix m_matWorld;
	CCube* m_pAxis[(uint32)Axis::END];
};

