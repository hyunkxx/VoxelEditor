#include "pch.h"
#include "..\Header\SaveLoader.h"

#include "Cube.h"
#include "CubeManager.h"

wstring CSaveLoader::m_strDirPath = L"..Bin/Resource/";

CSaveLoader::CSaveLoader()
{
}

CSaveLoader::~CSaveLoader()
{
}

void CSaveLoader::SaveFile()
{
	vector<CCube*> vecHead = CCubeManager::GetInstance()->GetHeadMesh();
	vector<CCube*> vecBody = CCubeManager::GetInstance()->GetBodyMesh();

	int headCubeCount = static_cast<int>(vecHead.size());
	int bodyCubeCount = static_cast<int>(vecBody.size());

	OPENFILENAME OFN;
	tchar filePathName[100] = L"";
	tchar lpstrFile[100] = L"";
	static tchar filter[] = L"Binary file\0*.bin";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = m_strDirPath.c_str();

	//매쉬파일 이름 _body , _head 자동분류 파일저장
	if (GetSaveFileName(&OFN))
	{
		DWORD dwRead = 0;
		vec3 transBuf[3];
		D3DXCOLOR colBuf;

		if (headCubeCount > 0)
		{
			wstring strFileEnd = L"_head.bin";
			wstring fileName = OFN.lpstrFile + strFileEnd;
			HANDLE hHead = CreateFile(
				fileName.c_str(),
				GENERIC_WRITE,
				0, NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			if (hHead == INVALID_HANDLE_VALUE)
			{
				MSG_BOX("failed hHead open");
				return;
			}

			WriteFile(hHead, &headCubeCount, sizeof(int), &dwRead, NULL);
			for (auto& iter = vecHead.begin(); iter != vecHead.end(); iter++)
			{
				vec3 scale = (*iter)->m_vScale;
				vec3 rotation; memcpy(&rotation, &(*iter)->m_Angle, sizeof(vec3));
				vec3 position = (*iter)->m_vPos;
				D3DXCOLOR color = (*iter)->dwColor;

				memcpy(&transBuf[0], &scale, sizeof(vec3));
				memcpy(&transBuf[1], &rotation, sizeof(vec3));
				memcpy(&transBuf[2], &position, sizeof(vec3));
				memcpy(&colBuf, &color, sizeof(D3DXCOLOR));

				WriteFile(hHead, transBuf[0], sizeof(vec3), &dwRead, NULL);
				WriteFile(hHead, transBuf[1], sizeof(vec3), &dwRead, NULL);
				WriteFile(hHead, transBuf[2], sizeof(vec3), &dwRead, NULL);
				WriteFile(hHead, &colBuf, sizeof(D3DXCOLOR), &dwRead, NULL);
			}
			CloseHandle(hHead);
		}

		if (bodyCubeCount > 0)
		{
			wstring strFileEnd = L"_body.bin";
			wstring fileName = OFN.lpstrFile + strFileEnd;
			HANDLE hBody = CreateFile(
				fileName.c_str(),
				GENERIC_WRITE,
				0, NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			if (hBody == INVALID_HANDLE_VALUE)
			{
				MSG_BOX("failed hBody open");
				return;
			}

			WriteFile(hBody, &bodyCubeCount, sizeof(int), &dwRead, NULL);
			for (auto& iter = vecBody.begin(); iter != vecBody.end(); iter++)
			{
				vec3 scale = (*iter)->m_vScale;
				vec3 rotation; memcpy(&rotation, &(*iter)->m_Angle, sizeof(vec3));
				vec3 position = (*iter)->m_vPos;
				D3DXCOLOR color = (*iter)->dwColor;

				memcpy(&transBuf[0], &scale, sizeof(vec3));
				memcpy(&transBuf[1], &rotation, sizeof(vec3));
				memcpy(&transBuf[2], &position, sizeof(vec3));
				memcpy(&colBuf, &color, sizeof(D3DXCOLOR));

				WriteFile(hBody, transBuf[0], sizeof(vec3), &dwRead, NULL);
				WriteFile(hBody, transBuf[1], sizeof(vec3), &dwRead, NULL);
				WriteFile(hBody, transBuf[2], sizeof(vec3), &dwRead, NULL);
				WriteFile(hBody, &colBuf, sizeof(D3DXCOLOR), &dwRead, NULL);
			}
			CloseHandle(hBody);
		}
	}
}

void CSaveLoader::LoadFile(CUBE_TYPE eType)
{
	switch (eType)
	{
	case CUBE_TYPE::HEAD:
		LoadHeadMesh();
		break;
	case CUBE_TYPE::BODY:
		LoadBodyMesh();
		break;
	case CUBE_TYPE::END:
		break;
	}
}

void CSaveLoader::RenderGUI()
{

}

void CSaveLoader::LoadHeadMesh()
{
	vector<CCube*> vecHead;

	OPENFILENAME OFN;
	tchar filePathName[100] = L"";
	tchar lpstrFile[100] = L"";
	static tchar filter[] = L"All file\0*.*\0Text file\0*.txt\0FBX file\0*.fbx";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = m_strDirPath.c_str();

	if (GetOpenFileName(&OFN))
	{
		HANDLE hHead = CreateFile(
			OFN.lpstrFile,
			GENERIC_READ,
			0, NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr);

		if (hHead == INVALID_HANDLE_VALUE)
		{
			MSG_BOX("failed hRead open");
			return;
		}

		char buf[100];
		ZeroMemory(&buf, sizeof(buf));

		DWORD dwRead = 0;
		
		int headCubeCount;
		char cntBuf[4];
		ZeroMemory(&cntBuf, sizeof(cntBuf));
		ReadFile(hHead, cntBuf, sizeof(int), &dwRead, NULL);
		headCubeCount = static_cast<int>(*cntBuf);

		for (int i = 0; i < headCubeCount; i++)
		{
			vec3 scale;
			vec3 rotation;
			vec3 position;
			D3DXCOLOR color;

			ZeroMemory(&scale, sizeof(vec3));
			ZeroMemory(&rotation, sizeof(vec3));
			ZeroMemory(&position, sizeof(vec3));
			ZeroMemory(&color, sizeof(D3DXCOLOR));

			ReadFile(hHead, buf, sizeof(vec3), &dwRead, NULL);
			memcpy(&scale, &buf, sizeof(vec3));

			ReadFile(hHead, buf, sizeof(vec3), &dwRead, NULL);
			memcpy(&rotation, &buf, sizeof(vec3));

			ReadFile(hHead, buf, sizeof(vec3), &dwRead, NULL);
			memcpy(&position, &buf, sizeof(vec3));

			ReadFile(hHead, buf, sizeof(D3DXCOLOR), &dwRead, NULL);
			memcpy(&color, &buf, sizeof(D3DXCOLOR));

			CCubeManager::GetInstance()->CreateCube(CUBE_TYPE::HEAD, scale, rotation, position, color);
		}
		CloseHandle(hHead);
	}
}

void CSaveLoader::LoadBodyMesh()
{
	vector<CCube*> vecBody;

	OPENFILENAME OFN;
	tchar filePathName[100] = L"";
	tchar lpstrFile[100] = L"";
	static tchar filter[] = L"All file\0*.*\0Text file\0*.txt\0FBX file\0*.fbx";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = m_strDirPath.c_str();

	if (GetOpenFileName(&OFN))
	{
		HANDLE hBody = CreateFile(
			OFN.lpstrFile,
			GENERIC_READ,
			0, NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr);

		if (hBody == INVALID_HANDLE_VALUE)
		{
			MSG_BOX("failed hRead open");
			return;
		}


		char buf[100];
		ZeroMemory(&buf, sizeof(buf));

		DWORD dwRead = 0;

		int bodyCubeCount;
		char cntBuf[4];
		ZeroMemory(&cntBuf, sizeof(cntBuf));
		ReadFile(hBody, cntBuf, sizeof(int), &dwRead, NULL);
		bodyCubeCount = static_cast<int>(*cntBuf);

		for ( int i = 0 ; i < bodyCubeCount ; i++ )
		{
			vec3 scale;
			vec3 rotation;
			vec3 position;
			D3DXCOLOR color;

			ZeroMemory(&scale, sizeof(vec3));
			ZeroMemory(&rotation, sizeof(vec3));
			ZeroMemory(&position, sizeof(vec3));
			ZeroMemory(&color, sizeof(D3DXCOLOR));

			ReadFile(hBody, buf, sizeof(vec3), &dwRead, NULL);
			memcpy(&scale, &buf, sizeof(vec3));

			ReadFile(hBody, buf, sizeof(vec3), &dwRead, NULL);
			memcpy(&rotation, &buf, sizeof(vec3));

			ReadFile(hBody, buf, sizeof(vec3), &dwRead, NULL);
			memcpy(&position, &buf, sizeof(vec3));

			ReadFile(hBody, buf, sizeof(D3DXCOLOR), &dwRead, NULL);
			memcpy(&color, &buf, sizeof(D3DXCOLOR));

			CCubeManager::GetInstance()->CreateCube(CUBE_TYPE::BODY, scale, rotation, position, color);
		}
		CloseHandle(hBody);
	}
}
