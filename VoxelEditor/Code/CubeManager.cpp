#include "pch.h"
#include "..\Header\CubeManager.h"

#include "Graphic.h"
#include "Cube.h"
#include "Ray.h"

IMPLEMENT_SINGLETON(CCubeManager)

const char* CCubeManager::current_item = "None";
bool CCubeManager::bHeadView	= true;
bool CCubeManager::bBoadView	= true;
bool CCubeManager::bObjectView  = true;

CCubeManager::CCubeManager()
	: m_rotAngle({ 0.f,0.f,0.f })
{
	ZeroMemory(&curColor, sizeof(ImVec4));

	m_vecHead.reserve(30);
	m_vecBody.reserve(30);
	m_vecObject.reserve(30);
}

CCubeManager::~CCubeManager()
{
	for (auto& iter = m_vecHead.begin(); iter != m_vecHead.end(); iter++)
		delete *iter;

	for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); iter++)
		delete *iter;

	for (auto& iter = m_vecObject.begin(); iter != m_vecObject.end(); iter++)
		delete *iter;
}

void CCubeManager::Update()
{
}

void CCubeManager::Render()
{
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	wstring headCount	= to_wstring(m_vecHead.size());
	wstring bodyCount	= to_wstring(m_vecBody.size());
	wstring objectCount = to_wstring(m_vecObject.size());

	wstring windowText = headCount + L" " + bodyCount + L" " + objectCount;
	SetWindowTextW(g_hWnd, windowText.c_str());

	if (bHeadView)
	{
		for (auto& iter = m_vecHead.begin(); iter != m_vecHead.end(); ++iter)
		{
			matrix matScale, matTrans, matRotation, matPRotation;
			matrix matRot[3]; 
			matrix matPRot[3];

			D3DXMatrixIdentity(&matTrans);
			D3DXMatrixIdentity(&matRotation);
			D3DXMatrixIdentity(&matPRotation);

			D3DXMatrixScaling(&matScale, (*iter)->m_vScale.x, (*iter)->m_vScale.y, (*iter)->m_vScale.z);

			D3DXMatrixRotationX(&matRot[2], D3DXToRadian((*iter)->m_Angle.x));
			D3DXMatrixRotationY(&matRot[1], D3DXToRadian((*iter)->m_Angle.y));
			D3DXMatrixRotationZ(&matRot[0], D3DXToRadian((*iter)->m_Angle.z));
			
			D3DXMatrixRotationX(&matPRot[2], D3DXToRadian(m_rotAngle.x));
			D3DXMatrixRotationY(&matPRot[1], D3DXToRadian(m_rotAngle.y));
			D3DXMatrixRotationZ(&matPRot[0], D3DXToRadian(m_rotAngle.z));

			matRotation = matRot[0] * matRot[1] * matRot[2];
			matPRotation = matPRot[0] * matPRot[1] * matPRot[2];

			D3DXMatrixTranslation(&matTrans, (*iter)->m_vPos.x, (*iter)->m_vPos.y, (*iter)->m_vPos.z);
			(*iter)->m_matWorld = matScale * matRotation * matTrans * matPRotation;

			CGraphic::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &(*iter)->m_matWorld);

			(*iter)->Render();
		}
	}

	if (bBoadView)
	{
		for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); ++iter)
		{
			matrix matScale, matTrans, matRotation, matPRotation;
			matrix matRot[3]; 
			matrix matPRot[3];

			D3DXMatrixIdentity(&matTrans);
			D3DXMatrixIdentity(&matRotation);
			D3DXMatrixIdentity(&matPRotation);

			D3DXMatrixScaling(&matScale, (*iter)->m_vScale.x, (*iter)->m_vScale.y, (*iter)->m_vScale.z);

			D3DXMatrixRotationX(&matRot[0], D3DXToRadian((*iter)->m_Angle.x));
			D3DXMatrixRotationY(&matRot[1], D3DXToRadian((*iter)->m_Angle.y));
			D3DXMatrixRotationZ(&matRot[2], D3DXToRadian((*iter)->m_Angle.z));

			D3DXMatrixRotationX(&matPRot[2], D3DXToRadian(m_rotAngle.x));
			D3DXMatrixRotationY(&matPRot[1], D3DXToRadian(m_rotAngle.y));
			D3DXMatrixRotationZ(&matPRot[0], D3DXToRadian(m_rotAngle.z));

			matRotation = matRot[0] * matRot[1] * matRot[2];
			matPRotation = matPRot[0] * matPRot[1] * matPRot[2];

			D3DXMatrixTranslation(&matTrans, (*iter)->m_vPos.x, (*iter)->m_vPos.y, (*iter)->m_vPos.z);
			(*iter)->m_matWorld = matScale * matRotation * matTrans * matPRotation;

			CGraphic::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &(*iter)->m_matWorld);

			(*iter)->Render();
		}
	}

	if (bObjectView)
	{
		for (auto iter = m_vecObject.begin(); iter != m_vecObject.end(); ++iter)
		{
			matrix matScale, matTrans, matRotation, matPRotation;
			matrix matRot[3];
			matrix matPRot[3];

			D3DXMatrixIdentity(&matTrans);
			D3DXMatrixIdentity(&matRotation);
			D3DXMatrixIdentity(&matPRotation);

			D3DXMatrixScaling(&matScale, (*iter)->m_vScale.x, (*iter)->m_vScale.y, (*iter)->m_vScale.z);

			D3DXMatrixRotationX(&matRot[2], D3DXToRadian((*iter)->m_Angle.x));
			D3DXMatrixRotationY(&matRot[1], D3DXToRadian((*iter)->m_Angle.y));
			D3DXMatrixRotationZ(&matRot[0], D3DXToRadian((*iter)->m_Angle.z));

			D3DXMatrixRotationX(&matPRot[2], D3DXToRadian(m_rotAngle.x));
			D3DXMatrixRotationY(&matPRot[1], D3DXToRadian(m_rotAngle.y));
			D3DXMatrixRotationZ(&matPRot[0], D3DXToRadian(m_rotAngle.z));

			matRotation = matRot[0] * matRot[1] * matRot[2];
			matPRotation = matPRot[0] * matPRot[1] * matPRot[2];

			D3DXMatrixTranslation(&matTrans, (*iter)->m_vPos.x, (*iter)->m_vPos.y, (*iter)->m_vPos.z);
			(*iter)->m_matWorld = matScale * matRotation * matTrans * matPRotation;

			CGraphic::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &(*iter)->m_matWorld);

			(*iter)->Render();
		}
	}
}

void CCubeManager::RenderUI()
{
	/* Inspecter */
	ShowInspector();
	ShowSelectedCubeInfo();
}

void CCubeManager::RenderIndex()
{
	if (all_object.empty())
		return;

	for (auto object = all_object.begin(); object != all_object.end(); ++object)
	{
		(*object)->RenderIndex();
	}
}

void CCubeManager::DeleteCube()
{
	if (m_pSeletedCube)
	{
		CUBE_TYPE type = m_pSeletedCube->m_eType;
		int32	  nID = m_pSeletedCube->m_nIndex;

		switch (type)
		{
		case CUBE_TYPE::HEAD:
			for (auto& iter = m_vecHead.begin(); iter != m_vecHead.end(); ++iter)
			{
				if (nID == (*iter)->m_nIndex)
				{
					for (auto& item = all_object.begin(); item != all_object.end(); ++item)
					{
						if (nID == (*item)->m_nIndex)
						{
							all_object.erase(item);
							break;
						}
					}
					 iter = m_vecHead.erase(iter);
					return;
				}
			}
			break;
		case CUBE_TYPE::BODY:
			for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); ++iter)
			{
				if (nID == (*iter)->m_nIndex)
				{
					for (auto& item = all_object.begin(); item != all_object.end(); ++item)
					{
						if (nID == (*item)->m_nIndex)
						{
							all_object.erase(item);
							break;
						}
					}

					m_vecBody.erase(iter);
					return;
				}
			}
			break;
		case CUBE_TYPE::OBJECT:
			for (auto& iter = m_vecObject.begin(); iter != m_vecObject.end(); ++iter)
			{
				if (nID == (*iter)->m_nIndex)
				{
					for (auto& item = all_object.begin(); item != all_object.end(); ++item)
					{
						if (nID == (*item)->m_nIndex)
						{
							all_object.erase(item);
							break;
						}
					}

					m_vecObject.erase(iter);
					return;
				}
			}
			break;
		default:
			MSG_BOX("m_pSeletedCube CUBE_TYPE Unknown");
			break;
		}

		delete m_pSeletedCube;
		m_pSeletedCube = nullptr;
	}
}

bool CCubeManager::Pick()
{
	Ray ray;
	float U, V, fDistance, fNear;
	fNear = 99999.f;

	m_pSeletedCube = nullptr;
	vector<CCube*>::iterator iterator;

	//헤드 + 바디
	vector<CCube*> m_vecCombine;
	for (auto& iter = m_vecHead.begin(); iter != m_vecHead.end(); ++iter)
		m_vecCombine.push_back(*iter);
	for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); ++iter)
		m_vecCombine.push_back(*iter);
	for (auto& iter = m_vecObject.begin(); iter != m_vecObject.end(); ++iter)
		m_vecCombine.push_back(*iter);

	for (auto& iter = m_vecCombine.begin(); iter != m_vecCombine.end() ; ++iter)
	{
		ZeroMemory(&ray, sizeof(Ray));
		//인스펙터 영역을 제외하고 피킹해야됨
		CRay::Raycast(&ray, (*iter)->m_matWorld);
#pragma region  피킹처리
		LPDIRECT3DVERTEXBUFFER9 pVB = (*iter)->GetVertexBuffer();
		Vertex* pVertex;
		pVB->Lock(0, 0, (void**)&pVertex, 0);

		if (D3DXIntersectTri(&pVertex[0].pos, &pVertex[1].pos, &pVertex[2].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[0].pos, &pVertex[2].pos, &pVertex[3].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[7].pos, &pVertex[6].pos, &pVertex[5].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[7].pos, &pVertex[5].pos, &pVertex[4].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[3].pos, &pVertex[2].pos, &pVertex[6].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[3].pos, &pVertex[6].pos, &pVertex[7].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[4].pos, &pVertex[5].pos, &pVertex[1].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[4].pos, &pVertex[1].pos, &pVertex[0].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[4].pos, &pVertex[0].pos, &pVertex[3].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[4].pos, &pVertex[3].pos, &pVertex[7].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[1].pos, &pVertex[5].pos, &pVertex[6].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}

		if (D3DXIntersectTri(&pVertex[1].pos, &pVertex[6].pos, &pVertex[2].pos,
			&ray.origin, &ray.dir, &U, &V, &fDistance))
		{
			if (fDistance < fNear)
			{
				fNear = fDistance;
				m_pSeletedCube = *iter;
			}
		}
		pVB->Unlock();	
#pragma endregion
	}

	if (m_pSeletedCube)
		return true;
	else
		return false;
}

void CCubeManager::DeleteMesh(CUBE_TYPE eType)
{
	switch (eType)
	{
	case CUBE_TYPE::HEAD:
		for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); ++iter)
		{
			delete *iter;
		}
		break;
	case CUBE_TYPE::BODY:
		for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); ++iter)
		{
			delete *iter;
		}
		break;
	case CUBE_TYPE::OBJECT:
		for (auto& iter = m_vecBody.begin(); iter != m_vecBody.end(); ++iter)
		{
			delete *iter;
		}
		break;
	}
	m_vecHead.clear();
	m_vecBody.clear();
	m_vecObject.clear();
}

void CCubeManager::ShowInspector()
{
	ImGui::SetNextWindowSize(ImVec2(IMGUI_INSPECTOR_WIDTH, 450));
	ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - IMGUI_INSPECTOR_WIDTH, 19));
	ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoResize);
	ImGui::TextColored(ImVec4(1, 1, 0, 5), "create option");
	ImGui::InputFloat3("  scale  ", fScale);
	ImGui::InputFloat3("  rotation  ", fRotation);
	ImGui::InputFloat3("  position  ", fPos);

	const char* items[] = { "Head", "Body", "Object", "None" };
	if (ImGui::BeginCombo("  cube type", current_item))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == items[n]);
			if (ImGui::Selectable(items[n], is_selected))
				current_item = items[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	static float color[4];
	if (ImGui::ColorPicker4("  cube color", color))
	{
		CCubeManager::GetInstance()->curColor = color;
	}

	if (ImGui::Button("Add Cube", ImVec2(140, IMGUI_BUT_HEIGHT)))
	{
		if (!strcmp(current_item, "Head"))
			CreateCube(CUBE_TYPE::HEAD, { fScale }, vec3(fRotation), { fPos }, color);
		if (!strcmp(current_item, "Body"))
			CreateCube(CUBE_TYPE::BODY, { fScale }, vec3(fRotation), { fPos }, color);
		if (!strcmp(current_item, "Object"))
			CreateCube(CUBE_TYPE::OBJECT, { fScale }, vec3(fRotation), { fPos }, color);
		if (!strcmp(current_item, "None"))
			MSG_BOX("박스 타입 지정하라고 했어 안했어 =ㅅ=");
	}
	ImGui::SameLine();

	if (ImGui::Button("Delete Cube", ImVec2(140, IMGUI_BUT_HEIGHT)) && m_pSeletedCube)
	{
		DeleteCube();
	}

	ImGui::TextColored(ImVec4(1, 1, 0, 5), "render options");
	ImGui::Checkbox(" head ", &bHeadView);
	ImGui::SameLine();
	ImGui::Checkbox(" body ", &bBoadView);
	ImGui::SameLine();
	ImGui::Checkbox(" object", &bObjectView);
	ImGui::SameLine();
	if (ImGui::Checkbox(" wire ", &bWireFrame))
	{
		if(bWireFrame)
			CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			CGraphic::GetInstance()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	ImGui::End();

#ifndef _DEBUG
	ImGui::ShowDemoWindow();
#endif

	ShowObjectList();
}

void CCubeManager::ShowSelectedCubeInfo()
{
	ImGui::SetNextWindowSize(ImVec2(IMGUI_INSPECTOR_WIDTH, 230));
	ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - IMGUI_INSPECTOR_WIDTH, 470));

	ImGui::Begin("Seleted Cube", nullptr, ImGuiWindowFlags_NoResize);
	ImGui::TextColored(ImVec4(1, 1, 0, 5), "selected cube info");

	if (m_pSeletedCube)
	{ 
		string strCubeInfo = " selected cube ID " + to_string(m_pSeletedCube->m_nIndex);
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0, 1, 0, 5), strCubeInfo.c_str());

		vec3 rotation;
		memcpy(&rotation, &m_pSeletedCube->m_Angle, sizeof(vec3));

		ImGui::InputFloat3("  scale", m_pSeletedCube->m_vScale);
		ImGui::SliderFloat3("  - scale", m_pSeletedCube->m_vScale, -0.1f, 100.f);

		ImGui::InputFloat3("  angle", rotation);
		ImGui::SliderFloat3("  - angle", rotation, 0.f, 360.f);
		memcpy(&m_pSeletedCube->m_Angle, &rotation, sizeof(Rotation));

		ImGui::InputFloat3("  pos", m_pSeletedCube->m_vPos);
		ImGui::SliderFloat3("  - pos", m_pSeletedCube->m_vPos, -10.f, 10.f);

		if (ImGui::Button("Transform Reset", ImVec2(IMGUI_INSPECTOR_WIDTH, IMGUI_BUT_HEIGHT)))
		{
			ZeroMemory(&m_pSeletedCube->m_Angle, sizeof(Rotation));
			ZeroMemory(&m_pSeletedCube->m_vPos, sizeof(vec3));

			m_pSeletedCube->m_vScale.x = 1.f;
			m_pSeletedCube->m_vScale.y = 1.f;
			m_pSeletedCube->m_vScale.z = 1.f;
		}

		ImVec4 color = ImGui::ColorConvertU32ToFloat4(curColor);
		ImGui::ColorButton(" selected color", { color.z,color.y,color.x,color.w }, 0, ImVec2(IMGUI_INSPECTOR_WIDTH, 20));
	}
	else
	{
		float temp[3]{ 0.f,0.f,0.f };
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 0, 0, 5), " nullptr");
		ImGui::InputFloat3("  scale", vec3(0.f, 0.f, 0.f));
		ImGui::SliderFloat3("", temp, 0, 0);
		ImGui::InputFloat3("  angle", vec3(0.f, 0.f, 0.f));
		ImGui::SliderFloat3("", temp, 0, 0);
		ImGui::InputFloat3("  pos", vec3(0.f, 0.f, 0.f));
		ImGui::SliderFloat3("", temp, 0, 0);
		
		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(ImVec4(0.f, 0.f, 1.f, 1.f), "NULL NULL NULL NULL NULL NULL NULL NULL");
		ImGui::TextColored(ImVec4(0.f, 0.f, 1.f, 1.f), "NULL NULL NULL NULL NULL NULL NULL NULL");
	}

	ImGui::End();
}

void CCubeManager::ShowObjectList()
{
	if (all_object.empty())
	{
		all_object.clear();
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(IMGUI_INSPECTOR_WIDTH, 270));
	ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - IMGUI_INSPECTOR_WIDTH, 700));
	ImGui::Begin("Object List", 0 , ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	
	ImGui::ListBoxHeader("cube", ImVec2(200, 400));

	for (auto iter = all_object.begin(); iter != all_object.end(); ++iter)
	{
		if (*iter == nullptr)
			continue;

		std::string& item_name = "object " + to_string((*iter)->m_nIndex);

		if (ImGui::Button(item_name.c_str(), ImVec2(150, 20)))
		{
			CCubeManager::GetInstance()->m_pSeletedCube = *iter;
			CCubeManager::GetInstance()->curColor = CCubeManager::GetInstance()->GetSeletedObject()->dwColor;
		}

		ImGui::SameLine();
		ImVec4 color = ImGui::ColorConvertU32ToFloat4((*iter)->dwColor);
		ImVec4 color_ = { color.z, color.y, color.x ,1.f };
		ImGui::ColorButton(item_name.c_str(), color_, 0, ImVec2(20, 20));
	}

	ImGui::ListBoxFooter();
	ImGui::End();
}

void CCubeManager::CreateCube(CUBE_TYPE eType, vec3 vScale, Rotation tagRotation, vec3 vPos, D3DXCOLOR color)
{
	CCube* pCube = new CCube(eType, vScale, tagRotation, vPos);

	if (FAILED(pCube->Initalize(color)))
	{
		SafeDelete(pCube);
		MSG_BOX("Failed Create Cube");
		return;
	}

	m_pSeletedCube = pCube;
	all_object.push_back(pCube);

	switch (eType)
	{
	case CUBE_TYPE::HEAD:
		m_vecHead.push_back(pCube);
		break;
	case CUBE_TYPE::BODY:
		m_vecBody.push_back(pCube);
		break;
	case CUBE_TYPE::OBJECT:
		m_vecObject.push_back(pCube);
		break;
	case CUBE_TYPE::END:
		MSG_BOX("박스 타입을 지정하세요 =ㅅ=");
		break;
	}
}
