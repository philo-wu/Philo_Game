#pragma once
#include "Snake.h"
#include "framework.h"

class Food
{
public:
	Food();
	~Food();

	void Initialize(ID2D1HwndRenderTarget* m_pRenderTarget);
	void Reset(Snake* snake ,bool isFoodOnBorderChecked);
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);
	bool GameWin = 0;
	POINT position;

private:

	ID2D1SolidColorBrush* m_pBlueBrush;
	ID2D1Bitmap* FoodBitmap;
};