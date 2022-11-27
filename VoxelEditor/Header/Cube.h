#pragma once

#include "VIBuffer.h"

class CCube : public CVIBuffer
{
public:
	explicit CCube();
	explicit CCube(CUBE_TYPE eType, vec3 vScale, Rotation tagAngle, vec3 m_vPos);

	virtual ~CCube();
public:
	matrix GetWorldMatrix() { return m_matWorld; };
	vec3 GetPosition() { return m_vPos; };
	virtual HRESULT Initalize() override;
	virtual HRESULT Initalize(D3DCOLOR color) override;
public:
	void ApplyColor();
	int32 GetMaxID() {	return s_nID;	};
public:
	CUBE_TYPE m_eType;
	int32 m_nIndex;

	matrix m_matWorld;
	vec3 m_vScale;
	vec3 m_vPos;
	Rotation m_Angle;

	D3DXCOLOR dwColor;
private:
	static int32 s_nID;
};

