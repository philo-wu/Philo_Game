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
	void Logic();
	void ClearDraw(HWND hWnd);
	// 結算number對應金額
	void Settlement(int number , bool pAutoing) {
		if (number == RED_ONCEMORE_NUMBER) {
			// 清空左邊四個
			for (int i = 0; i < 4; ++i) {
				if (pAutoing) {
					if (!CostScore((Get_CellScore(i) * Bet_call_map[i]))) {
						MessageBox(NULL, L"金額不足,關閉自動模式", L"錯誤", MB_OK);
						autoing = 0;
					}
				}
				else {
					Bet_call_map[i] = 0;
				}
			}
		}
		else if (number == BLUE_ONCEMORE_NUMBER) {
			// 清空右邊四個
			for (int i = 4; i < CELL_TOTAL; ++i) {
				if (pAutoing) {
					if (!CostScore((Get_CellScore(i) * Bet_call_map[i]))) {
						MessageBox(NULL, L"金額不足,關閉自動模式", L"錯誤", MB_OK);
						autoing = 0;
					}
				}
				else {
					Bet_call_map[i] = 0;
				}
			}
		}
		else {
			int cost = Get_CellScore(number);
			AddWinScore(Bet_call_map[number] * cost * 2); //2為花費加上回報
			for (int i = 0; i < CELL_TOTAL; ++i) {
				if (autoing) {
					if (!CostScore((Get_CellScore(i) * Bet_call_map[i]))){
						MessageBox(NULL, L"金額不足,關閉自動模式", L"錯誤", MB_OK);
						autoing = 0;
					}
				}
				else {
					Bet_call_map[i] = 0;
				}
			}
		}
	};
	void AddWinScore(int cost) { 
		WinScore += cost;
		return; 
	}

	bool CostWinScore(int cost) {  
		WinScore -= cost;
		if (Score >= 0)
			return true;
		else
			WinScore += cost;
		return false;
	}
	// 結算WinScore 到Score
	void WinToScore() {
		Score += WinScore;
		WinScore=0;
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
	int GetWinScore() { return WinScore; }
	int GetScore() { return Score; }

	void SetBigOrSmall(bool number) {
		if (number == 0)
			compare_SmallOrBig = 0;
		else if (number == 1 )
			compare_SmallOrBig = 1;
	}

	bool playing = 0; //位於遊戲畫面中
	bool bet_starting = 0; //按下開始遊戲
	bool bet_started = 0; //有開始過遊戲
	bool bet_settling = 0; //等待結算

	bool compare_starting = 0; //按下大小
	bool compare_SmallOrBig = 0; // 0=小 1=大
	bool compare_settling = 0; //等待結算


	bool idleing = 0; //閒置中
	bool autoing = 0; //自動執行
	int run_second = 10; //每圈執行秒數 
	int position = 0 ; //起點位置
	int endPosition = 0; //終點位置
	int endCompare = 0;
	int Comparenumber = 0;

	long long currentTime;
	long long endTime;


	std::multimap<int, std::pair<int, bool>> Bet_Light_call_map; //紀錄操控動作   <時間,<號碼,燈亮或暗>>
	std::multimap<int, std::pair<int, bool>> Game_Light_call_map; //紀錄操控動作  <時間,<號碼,燈亮或暗>>
	std::multimap<int, std::pair<int, bool>> Compare_Light_call_map; //紀錄操控動作  <時間,<號碼,燈亮或暗>>
	std::multimap<int, int> Compare_Number_map; //紀錄操控動作  <時間,數字>


	HRESULT Draw();
	void Draw_Cell_Text(int number, D2D1_RECT_F Rect);
	void Draw_Cell(int number , D2D1_RECT_F Rect);
	void Draw_Game(int x ,int y ,int width ,int height);
	void Draw_Bet(int x, int y, int width, int height);
	void Draw_Function(int x, int y, int width, int height);
	int Get_CellScore(int number);
	int Get_CellNumber(int light_number);
	void Bet_call(int number , int amount);
	void updateLightStatus();
	void SetLightStatus(std::multimap<int, std::pair<int, bool>> &map,int time , int number,bool islight);
	bool isLight(std::map<int, bool> map, int number);
	void SetCompareNumber(int time, int number);


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
	int WinScore;
	int Score;

	int lightsecond = 200; //燈亮時間
	int lightsecond_slow = 400; //燈長亮時間
	int lightIndex = 0;  
	int lightIndex_slow = 0;

	std::map<int, int> Bet_call_map; //紀錄下注狀況  <號碼,金額>
	std::map<int, bool >Bet_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>
	std::map<int, bool> Game_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>
	std::map<int, bool> Compare_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>

};
