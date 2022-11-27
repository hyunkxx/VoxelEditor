#pragma once
class CRay
{
	DECLARE_SINGLETON(CRay)
private:
	CRay();
	~CRay();
public:
	static void Raycast(Ray* out_pRay, const matrix& matWorld);
};

