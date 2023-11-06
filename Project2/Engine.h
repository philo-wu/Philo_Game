#pragma once
#include <chrono>



class Engine
{
public:
	Engine(Common* pcommon);
	~Engine();

	Common* common;
	HRESULT InitializeD2D(HWND m_hwnd);
	void KeyUp(WPARAM wParam);
	void Reset();
	void Logic(double elapsedTime);
	void ClearDraw(HWND hWnd);

	int getscore() { return score; };
	//void fps_count();
	std::chrono::system_clock::time_point lastTime;

	int run_second = 10; //每圈執行秒數 
	int position ; //當前運行位置

	HRESULT Draw();
	bool playing = 0;
	int difficulty = 5;
	void Draw_Cell_Text(int number, D2D1_RECT_F Rect);

	void Draw_Cell(int number , D2D1_RECT_F Rect);
	void Draw_Game(int x ,int y ,int width ,int height);
	void Draw_Bet(int x, int y, int width, int height);
	void Draw_Function(int x, int y, int width, int height);
	int Get_CellScore(int number);
private:
	ID2D1Factory* m_pDirect2dFactory ;
	ID2D1HwndRenderTarget* m_pRenderTarget ;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;

	//Snake* snake;
	//Food* food;	
	ID2D1Bitmap* AppleBitmap;
	ID2D1Bitmap* BarBitmap;
	ID2D1Bitmap* BellBitmap;
	ID2D1Bitmap* LemonBitmap;
	ID2D1Bitmap* OrangeBitmap;
	ID2D1Bitmap* SevenBitmap;
	ID2D1Bitmap* StarBitmap;
	ID2D1Bitmap* WatermelonBitmap;

	ID2D1Bitmap* BackgroundBitmap;
	ID2D1Bitmap* Mid_BackgroundBitmap;

	json BettingTable;
	int score;
	int highScore;

	bool keyPressed;

	std::map<int, int> Bet_call_map; //紀錄下注狀況
	std::map<int, std::pair<int, int>> Bet_Light_call_map; //紀錄燈亮時間
	std::map<int, std::pair<int, int>> Game_Light_call_map; //紀錄燈亮時間

};
