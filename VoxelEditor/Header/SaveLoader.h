#pragma once

class CSaveLoader
{
private:
	explicit CSaveLoader();
	~CSaveLoader();
public:
	static wstring GetDirectoryPath() { return m_strDirPath; }
	static void SetDirectoryPath(wstring strDirectoryPath) { m_strDirPath = strDirectoryPath; };

	static void SaveFile();
	static void LoadFile(CUBE_TYPE eType);
	static void RenderGUI();
private:
	static void LoadHeadMesh();
	static void LoadBodyMesh();
	static void LoadObjectMesh();
private:
	static wstring m_strDirPath;
};

/*  4byte 12byte 12byte 12byte   16byte  68byte?*/
// [size][scale][angle][position][color]