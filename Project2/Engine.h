#pragma once
#include "Food.h"
#include "Snake.h"
#include <chrono>



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
	int getscore() { return score; };
	int FPS = 0;
	void fps_count();
	std::chrono::system_clock::time_point lastTime;

	HRESULT Draw();
	bool playing = 0;
	int difficulty = 5;
	double UpdateFrameSleep(int difficulty);
	bool isFoodOnBorderChecked = 0;

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

	bool keyPressed;
};
