#pragma once

#include "Food.h"
#include "Snake.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAME_SLEEP 100
#define CELL_SIZE 20

class Engine
{
public:
	Engine();
	~Engine();

	HRESULT InitializeD2D(HWND m_hwnd);
	void KeyUp(WPARAM wParam);
	void Reset();
	void Logic(double elapsedTime);
	HRESULT Draw();

private:
	ID2D1Factory* m_pDirect2dFactory ;
	ID2D1HwndRenderTarget* m_pRenderTarget ;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;

	Snake* snake;
	Food* food;

	int score;
	int highScore;

	bool playing;
	bool keyPressed;
};
