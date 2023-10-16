#pragma once

#include "Tree.h"

class Engine
{
public:
	Engine();
	~Engine();


	HRESULT InitializeD2D(HWND m_hwnd);
	void Logic(double elapsedTime);///種樹暫時無邏輯 保留架構
	void ClearDraw(HWND hWnd);

	HRESULT Draw(POINT point ,int pxSize,Tree* tree);
	bool frist_start = 1;
	bool do_clear = 1;
	bool do_drawMap = 0;

	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;


private:

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;


};
