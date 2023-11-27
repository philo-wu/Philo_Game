#pragma once
#include <chrono>
#include "Area_Bet.h"
#include "Area_Function.h"
#include "Area_Game.h"



class Engine
{
public:
	Engine(Common* pcommon , HWND p_hwnd);
	~Engine();

	HWND m_hwnd;
	Common* common;
	Area_Bet* m_area_Bet ;
	Area_Function* m_area_Function ;
	Area_Game* m_area_Game ;

	HRESULT InitializeD2D();
	void KeyUp(WPARAM wParam);
	void Reset();
	void Logic();
	void ClearDraw();

	bool playing = 0; //位於遊戲畫面中

	HRESULT Draw();

	void Logic_auto();
private:
	ID2D1Factory* m_pDirect2dFactory ;
	ID2D1HwndRenderTarget* m_pRenderTarget ;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;

	json BettingTable;
};
