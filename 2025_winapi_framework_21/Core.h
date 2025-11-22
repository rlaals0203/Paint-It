#pragma once
//include "Object.h"
class Core
{
	DECLARE_SINGLE(Core);
public:
public:
	bool Init(HWND _hWnd);
	void GameLoop();
	void CleanUp();
public:
	const HWND& GetHwnd() const { return m_hWnd; }
	const HDC& GetMainDC() const { return m_hDC; }
private:
	void MainUpdate();
	void MainRender();
private:
	HWND m_hWnd;
	HDC  m_hDC;
	//Object m_obj;
	// 더블버퍼링
	HBITMAP m_hBackBit;
	HDC  m_hBackDC;
};