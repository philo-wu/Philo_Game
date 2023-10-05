#include "framework.h"
#include "Food.h"
#include "Engine.h"

Food::Food() : m_pBlueBrush(NULL)
{
}

Food::~Food()
{
	//SafeRelease(&m_pBlueBrush);
	SafeRelease(&FoodBitmap);
}

void Food::Initialize(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Creates a blue brush for drawing
	//m_pRenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Blue),
	//	&m_pBlueBrush
	//);
	
	// �����ŧi�Ϥ�
	// �L�k�ϥΰѦҸ��|,���ϥε�����|
	LPCWSTR filePath = L"./Images/Food.png";;
	IWICImagingFactory* pIWICFactory = NULL;
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
	Common:: LoadBitmapFromFile(m_pRenderTarget, pIWICFactory, filePath, 0, 0, &FoodBitmap);
	pIWICFactory->Release();

}

void Food::Reset(Snake* snake , bool isFoodOnBorderChecked)
{
	srand((unsigned)time(NULL));
	std::vector<std::pair<int, int>> validPositions;
	// �ϥ�vector�������Q�ϥιL����l,�ñq�䤤�ͦ��s������
	//for (int x = 1; x < SCREEN_WIDTH / CELL_SIZE - 1; ++x)
	//{
	//	for (int y = 1; y < SCREEN_HEIGHT / CELL_SIZE - 1; ++y)
	//	{
	//		bool isOccupied = false;

	//		for (int i = 0; i < snake->length; ++i)
	//		{
	//			if (snake->position[i].x == x && snake->position[i].y == y)
	//			{
	//				isOccupied = true;
	//				break;
	//			}
	//		}

	//		if (!isOccupied)
	//		{
	//			validPositions.push_back(std::make_pair(x, y));
	//		}
	//	}
	//}

	for (int y = 0; y < SCREEN_HEIGHT / CELL_SIZE; ++y)
	{
		// �ˬd�O�_�b���
		if (!isFoodOnBorderChecked)
		{
			if (y == 0 || y == SCREEN_HEIGHT / CELL_SIZE - 1)
			{
				continue;  // ���L��ɤW����m
			}
		}

		for (int x = 0; x < SCREEN_WIDTH / CELL_SIZE; ++x)
		{
			bool isOccupied = false;
			if (!isFoodOnBorderChecked)
			{
				if (x == 0 || x == SCREEN_WIDTH / CELL_SIZE - 1)
				{
					continue;  // ���L��ɤW����m
				}
			}
			for (int i = 0; i < snake->length; ++i)
			{
				if (snake->position[i].x == x && snake->position[i].y == y)
				{
					isOccupied = true;
					break;
				}
			}

			if (!isOccupied)
			{
				validPositions.push_back(std::make_pair(x, y));
			}
		}
	}
	if (!validPositions.empty())
	{
		GameWin = 0;
		// �H����ܤ@�ӦX�A����l
		int randomIndex = rand() % validPositions.size();
		position.x = validPositions[randomIndex].first;
		position.y = validPositions[randomIndex].second;
	}
	else
	{
		// TODO:�C���ӧQ
		GameWin = 1;
		// �bEngineŪ�����ܼ�
	}

	
}

void Food::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Draws the food using Direct2D
	// ����ø�s�Ϥ�
	//D2D1_ELLIPSE ellipseBall = D2D1::Ellipse(
	//	D2D1::Point2F(position.x * CELL_SIZE + CELL_SIZE / 2, position.y * CELL_SIZE + CELL_SIZE / 2),
	//	CELL_SIZE / 2, CELL_SIZE / 2
	//);
	//m_pRenderTarget->FillEllipse(&ellipseBall, m_pBlueBrush);
	if (FoodBitmap)
	{
		D2D1_SIZE_F size = FoodBitmap->GetSize();

		D2D1_RECT_F destinationRect = D2D1::RectF(
			position.x * CELL_SIZE,
			position.y * CELL_SIZE,
			(position.x + 1) * CELL_SIZE,
			(position.y + 1) * CELL_SIZE
		);

		m_pRenderTarget->DrawBitmap(FoodBitmap, destinationRect);
	}
}