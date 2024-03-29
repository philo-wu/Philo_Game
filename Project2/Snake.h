﻿#pragma once

#include "framework.h"
#include "Direct2D.h"

struct Point2D
{
	int x;
	int y;
};

class Snake
{
public:
	Snake();
	~Snake();

	void Initialize(ID2D1HwndRenderTarget* m_pRenderTarget);
	void GoUp();
	void GoDown();
	void GoLeft();	
	void GoRight();
	void Reset();
	void Advance();
	bool CheckSelfCollision();
	bool CheckFoodCollision(int x, int y);
	void Grow();
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);
	float CalculateRotationAngle(POINT point1, POINT point2);

	POINT position[1000];
	POINT direction;
	int length;


private:

	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1Bitmap* HeadBitmap;
	ID2D1Bitmap* BodyBitmap;
	ID2D1Bitmap* TailBitmap;


};
