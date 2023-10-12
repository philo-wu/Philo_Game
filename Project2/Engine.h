#pragma once

#include "Tree.h"

class Engine
{
public:
	Engine();
	~Engine();

	HRESULT InitializeD2D(HWND m_hwnd);
	void KeyUp(WPARAM wParam);
	void Reset();
	void Logic(double elapsedTime);
	void ClearDraw(HWND hWnd);

	HRESULT Draw();
	bool playing = 0;
	bool isFoodOnBorderChecked = 0;



private:
	ID2D1Factory* m_pDirect2dFactory ;
	ID2D1HwndRenderTarget* m_pRenderTarget ;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;


};
