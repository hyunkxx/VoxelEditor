#pragma once

#include "GameObject.h"

#include "Cube.h"

class CCamera : public CGameObject
{
public:
	enum class VIEW { FORWARD, BACKWARD, RIGHT, LEFT, UP, DOWN, MAX};
public:
	CCamera(LPDIRECT3DDEVICE9 pDevice);
	~CCamera();
public:
	virtual void Initalize() override;
	virtual void Update(const double & fDeltaTime) override;
	virtual void Render() override;
	virtual void RenderUI() override;
public:
	void OhtoCamera();
	void SetupCamera(const vec3& vPos, const vec3& At);
	void TransformSetting();
public:
	const vec3& GetPosition() const { return m_vPos; };
	vec3 GetDirection() const { return m_vAt - m_vPos; }
	const vec3& GetLookAt() const { return m_vAt; }

public: 
	bool ChangeView();

private:
	void Zoom();
	void Movement();
	void KeyRotation();
	void MouseRotation();
private:
	bool CameraState[(UINT)VIEW::MAX];

	vec3 vUp;
	vec3 vRight;
	vec3 vLook;

	float m_fMoveSpeed;
	float m_fDistance;

	const vec3 vUP = { 0.f ,1.f ,0.f };
	/* Camera Matrix */
	matrix m_matView;
	matrix m_matProj;
	/* Camera Settring Value */
	vec3 m_vPos;
	vec3 m_vAt;

	float m_fHeight;
	float m_fWidth;
	float m_fFOV;

	float m_fOrthoX = 10.f;
	float m_fOrthoY = 10.f;
};

