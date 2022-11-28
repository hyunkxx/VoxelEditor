#pragma once
class CInputManager
{
private:
	CInputManager();
	~CInputManager();
public:
	static void KeyInput();
private:
	static void SaveLoadCheck();
	static void DeleteCube();
	static void MouseLeftButton();
	static void KeyObjectMove();
	static void ColorPickChange();
	static void ObjectClone();
};

