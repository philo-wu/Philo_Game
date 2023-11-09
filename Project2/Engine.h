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
	void AddWindScore(int score) {WindScore += score;};
	bool CostWindScore(int cost) { 
		WindScore -= cost;
		if (Score >= 0)
			return true;
		else
			WindScore += cost;
		return false;
	}
	int GetWindScore() { return WindScore; };
	void CloseScore() { 
		Score += WindScore;
		WindScore=0;
	}
	bool CostScore(int cost) { 
		Score -= cost;
		if (Score >= 0)
			return true;
		else
			Score += cost;
		return false;
	}
	void AddScore(int score) { Score += score; }
	int GetScore() { return Score; }

	//void fps_count();

	bool playing = 0; //位於遊戲畫面中
	bool starting = 0; //按下開始遊戲
	int run_second = 10; //每圈執行秒數 
	int position = 0 ; //當前運行位置
	int end_position = 0;
	long long currentTime;
	

	std::multimap<int, std::pair<int, bool>> Bet_Light_call_map; //紀錄操控動作   <時間,<號碼,燈亮或暗>>
	std::multimap<int, std::pair<int, bool>> Game_Light_call_map; //紀錄操控動作  <時間,<號碼,燈亮或暗>>
	std::multimap<int, std::pair<int, bool>> Compare_Light_call_map; //紀錄操控動作  <時間,<號碼,燈亮或暗>>


	HRESULT Draw();
	void Draw_Cell_Text(int number, D2D1_RECT_F Rect);
	void Draw_Cell(int number , D2D1_RECT_F Rect);
	void Draw_Game(int x ,int y ,int width ,int height);
	void Draw_Bet(int x, int y, int width, int height);
	void Draw_Function(int x, int y, int width, int height);
	int Get_CellScore(int number);
	void Bet_call(int number , int amount);
	void updateLightStatus();
	void SetLightStatus(std::multimap<int, std::pair<int, bool>> &map,int time , int number,bool islight);
	bool isLight(std::map<int, bool> map, int number);


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
	int WindScore;
	int Score;


	std::map<int, int> Bet_call_map; //紀錄下注狀況  <號碼,金額>
	std::map<int, bool >Bet_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>
	std::map<int, bool> Game_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>
	std::map<int, bool> Compare_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>

};
