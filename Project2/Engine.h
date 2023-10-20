#pragma once

#include "Tree.h"

class Engine
{
public:
	Engine();
	~Engine();


	HRESULT InitializeD2D(HWND m_hwnd);
	void Logic(double elapsedTime);																			//種樹無邏輯 保留架構
	void ClearDraw(HWND hWnd);

	D2D1_RECT_F Rect_functionColumn = D2D1::RectF(0, 0, SCREEN_WIDTH, FUNCTION_COLUMN_HEIGHT);				//視窗上方功能列
	D2D1_RECT_F Rect_drawingArea = D2D1::RectF(0, FUNCTION_COLUMN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);		//視窗下方繪圖區域

	HRESULT Draw(POINT point ,int OriginalSize,int pxSize, FruitTree* tree ,
		json Map_saveData, json Tree_saveData,std::vector<POINT> Map_treepoints);
	bool frist_start = 1;
	bool do_clear = 1;
	bool do_drawMap = 0;
	ID2D1Bitmap* Map_Bitmap;


	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	HWND phWnd;

private:

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	std::filesystem::path currentPath = std::filesystem::current_path(); // C++ 17


};
