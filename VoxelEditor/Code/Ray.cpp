#include "pch.h"
#include "..\Header\Ray.h"

#include "Graphic.h"

IMPLEMENT_SINGLETON(CRay)

CRay::CRay()
{
}


CRay::~CRay()
{
}

void CRay::Raycast(Ray* out_pRay, const matrix& matWorld)
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);

	matrix matProj, matView;
	D3DVIEWPORT9 viewport;
	ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));
	Ray ray;
	vec3 vMouse;

	CGraphic::GetInstance()->GetDevice()->GetViewport(&viewport);

	vMouse.x = mouse.x /  (viewport.Width  * 0.5f)  - 1.f;
	vMouse.y = mouse.y / -(viewport.Height * 0.5f) + 1.f;
	vMouse.z = 0.f;

	CGraphic::GetInstance()->GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, 0, &matProj);
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);

	ray.origin = { 0.f, 0.f, 0.f };
	ray.dir = vMouse - ray.origin;

	CGraphic::GetInstance()->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);
	D3DXVec3TransformCoord(&ray.origin, &ray.origin, &matView);
	D3DXVec3TransformNormal(&ray.dir, &ray.dir, &matView);
	
	matrix world = matWorld;
	D3DXMatrixInverse(&world, 0, &world);
	D3DXVec3TransformCoord(&ray.origin, &ray.origin, &world);
	D3DXVec3TransformNormal(&ray.dir, &ray.dir, &world);

	*out_pRay = ray;
}
