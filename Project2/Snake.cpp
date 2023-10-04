#include "Snake.h"
#include "Engine.h"
#include "Food.h"
#include "framework.h"

Snake::Snake() : m_pGreenBrush(NULL), m_pRedBrush(NULL)
{
	Reset();
}

Snake::~Snake()
{
	//SafeRelease(&m_pGreenBrush);
	//SafeRelease(&m_pRedBrush);
	SafeRelease(&HeadBitmap);
	SafeRelease(&BodyBitmap);
	SafeRelease(&TailBitmap);

}

void Snake::Initialize(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Creates a green and red brush for drawing
	//m_pRenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Green),
	//	&m_pGreenBrush
	//);
	//m_pRenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Red),
	//	&m_pRedBrush
	//);
	
	// 換成宣告圖片
	// 無法使用參考路徑,先使用絕對路徑
	LPCWSTR filePath;
	IWICImagingFactory* pIWICFactory = NULL;
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);

	filePath = L"C:/Users/philo.wu/Documents/GitHub/Philo_Snake/Project2/Images/Snake_Head.png";
	Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, filePath, 0, 0, &HeadBitmap);
	filePath = L"C:/Users/philo.wu/Documents/GitHub/Philo_Snake/Project2/Images/Snake_Body.png";
	Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, filePath, 0, 0, &BodyBitmap);
	filePath = L"C:/Users/philo.wu/Documents/GitHub/Philo_Snake/Project2/Images/Snake_Tail.png";
	Common::LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, filePath, 0, 0, &TailBitmap);

	pIWICFactory->Release();
}

void Snake::Reset()
{
	length = 5;

	direction.x = 1;
	direction.y = 0;

	for (int i = 0; i < length; i++)
	{
		position[i].x = 10 - i;
		position[i].y = 10;
	}
}

void Snake::GoUp()
{
	if (direction.y == 0)
	{
		direction.x = 0;
		direction.y = -1;
	}
}
void Snake::GoDown()
{
	if (direction.y == 0)
	{
		direction.x = 0;
		direction.y = 1;
	}
}
void Snake::GoLeft()
{
	if (direction.x == 0)
	{
		direction.x = -1;
		direction.y = 0;
	}
}
void Snake::GoRight()
{
	if (direction.x == 0)
	{
		direction.x = 1;
		direction.y = 0;
	}
}

void Snake::Advance()
{
	for (int i = length - 1; i > 0; i--)
	{
		position[i].x = position[i - 1].x;
		position[i].y = position[i - 1].y;
	}
	position[0].x = position[0].x + direction.x;
	position[0].y = position[0].y + direction.y;
}

bool Snake::CheckSelfCollision()
{
	for (int i = 1; i < length; i++)
	{
		if (position[0].x == position[i].x && position[0].y == position[i].y)
		{
			return true;
		}
	}
	if (position[0].x < 0) return true;
	if (position[0].y < 0) return true;
	if (position[0].x >= SCREEN_WIDTH / CELL_SIZE) return true;
	if (position[0].y >= SCREEN_HEIGHT / CELL_SIZE) return true;
	return false;
}

bool Snake::CheckFoodCollision(int x, int y)
{
	if (position[0].x == x && position[0].y == y)
	{
		return true;
	}
	return false;
}

void Snake::Grow()
{
	position[length].x = position[length - 1].x;
	position[length].y = position[length - 1].y;
	length++;
}

void Snake::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Draws the snake using Direct2D
	// 
	// Snake Body
	//for (int i = 1; i < length; i++)
	//{
	//	D2D1_ELLIPSE ellipseBall = D2D1::Ellipse(
	//		D2D1::Point2F(position[i].x * CELL_SIZE + CELL_SIZE / 2, position[i].y * CELL_SIZE + CELL_SIZE / 2),
	//		CELL_SIZE / 2, CELL_SIZE / 2
	//	);
	//	m_pRenderTarget->FillEllipse(&ellipseBall, m_pGreenBrush);
	//}

	//// Snake Head
	//D2D1_ELLIPSE ellipseBall = D2D1::Ellipse(
	//	D2D1::Point2F(position[0].x * CELL_SIZE + CELL_SIZE / 2, position[0].y * CELL_SIZE + CELL_SIZE / 2),
	//	CELL_SIZE / 2, CELL_SIZE / 2
	//);
	//m_pRenderTarget->FillEllipse(&ellipseBall, m_pRedBrush);
	
	
	// 換成繪製圖片
	for (int i = 1; i < length - 1; i++)
	{
		D2D1_RECT_F destRect = D2D1::RectF(
			position[i].x * CELL_SIZE,
			position[i].y * CELL_SIZE,
			(position[i].x + 1) * CELL_SIZE,
			(position[i].y + 1) * CELL_SIZE
		);
		m_pRenderTarget->DrawBitmap(BodyBitmap, destRect);
	}

	// 蛇的尾巴
	float tailRotationAngle = CalculateRotationAngle(position[length - 2], position[length - 1 ]);
	D2D1_RECT_F destRectTail = D2D1::RectF(
		position[length - 1].x * CELL_SIZE,
		position[length - 1].y * CELL_SIZE,
		(position[length - 1].x + 1) * CELL_SIZE,
		(position[length - 1].y + 1) * CELL_SIZE
	);
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(tailRotationAngle, D2D1::Point2F(destRectTail.left + CELL_SIZE / 2, destRectTail.top + CELL_SIZE / 2)));
	m_pRenderTarget->DrawBitmap(TailBitmap, destRectTail);

	// 蛇的頭部分
	float headRotationAngle = CalculateRotationAngle(position[0], position[1]);
	D2D1_RECT_F destRectHead = D2D1::RectF(
		position[0].x * CELL_SIZE,
		position[0].y * CELL_SIZE,
		(position[0].x + 1) * CELL_SIZE,
		(position[0].y + 1) * CELL_SIZE
	);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(headRotationAngle, D2D1::Point2F(destRectHead.left + CELL_SIZE / 2, destRectHead.top + CELL_SIZE / 2)));
	m_pRenderTarget->DrawBitmap(HeadBitmap, destRectHead);

	// 還原轉換
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

//根據下一點移動方向決定轉向
float Snake::CalculateRotationAngle(POINT point1, POINT point2)
{
	float dx = point2.x - point1.x;
	float dy = point2.y - point1.y;
	return atan2(dy, dx) * (180.0f / 3.1415926535f);
}