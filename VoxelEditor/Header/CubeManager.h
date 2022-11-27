#pragma once

class CCube;

class CCubeManager
{
	DECLARE_SINGLETON(CCubeManager)
private:
	CCubeManager();
	~CCubeManager();
public:
	void Update();
	void Render();
	void RenderUI();

	void CreateCube(CUBE_TYPE eType,vec3 vScale, Rotation tagRotation, vec3 vPos, D3DXCOLOR color);
	void DeleteCube();

	bool Pick();

	const Rotation& GetAngle() { return m_rotAngle; }
	void ResetAngle() { m_rotAngle = { vec3(0.f, 0.f, 0.f) }; };

	vector<CCube*> GetHeadMesh() { return m_vecHead; }
	vector<CCube*> GetBodyMesh() { return m_vecBody; }

	void DeleteMesh(CUBE_TYPE eType);
	CCube* GetSeletedObject() { return m_pSeletedCube; }
public:
	void ShowInspector();
	void ShowSelectedCubeInfo();
	void ShowObjectList();
public:
	vector<CCube*> m_vecHead;
	vector<CCube*> m_vecBody;

	vector<CCube*> all_object;

	Rotation m_rotAngle;

	D3DXCOLOR curColor;
private: //ImGui values
	bool bWireFrame = false;

	static float fScale[3];
	static float fRotation[3];
	static float fPos[3];

	static const char* current_item;
	static bool bHeadView, bBoadView;
	//피킹에서 포인터 갖고있는데 문제될수있음 추후에 삭제코드 변경
	CCube* m_pSeletedCube = nullptr;
};
