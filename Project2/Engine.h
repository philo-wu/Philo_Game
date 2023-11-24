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

	Area_Bet* m_area_Bet ;
	Area_Function* m_area_Function ;
	Area_Game* m_area_Game ;
	/*
	0 = 閒置

	1 = 遊戲_bet
	2 = 結算_bet
	3 = 遊戲_Compare
	4 = 結算_Compare
	*/

	Common* common;
	HWND m_hwnd;
	HRESULT InitializeD2D();
	void KeyUp(WPARAM wParam);
	void Reset();
	void Logic();
	void ClearDraw();
	// 結算number對應金額

	bool playing = 0; //位於遊戲畫面中




	std::multimap<int, std::pair<int, bool>> Bet_Light_call_map; //紀錄操控動作   <時間,<號碼,燈亮或暗>>
	std::multimap<int, std::pair<int, bool>> Game_Light_call_map; //紀錄操控動作  <時間,<號碼,燈亮或暗>>
	std::multimap<int, std::pair<int, bool>> Compare_Light_call_map; //紀錄操控動作  <時間,<號碼,燈亮或暗>>
	std::multimap<int, int> Compare_Number_map; //紀錄操控動作  <時間,數字>


	HRESULT Draw();

	void Logic_Bet();
	void Logic_Compare();
	void Logic_settle();
	void Logic_idle();
	void Logic_auto();

	int Get_CellScore(int number);
	int Get_CellNumber(int light_number);
	
	// 判斷是否有下注
	bool CheckBet();
	// 投入金額 0為清空
	void Bet_call(int number , int amount);
	// 處理指令
	void updateLightStatus();
	// 下達燈號指令
	void SetLightStatus(std::multimap<int, std::pair<int, bool>> &map,int time , int number,bool islight);
	// 下達大小指令
	void SetCompareNumber(int time, int number);
	// 將燈號全部關閉
	void Light_Clear();

#ifdef NOUSE
	void Settlement(int number, bool pAutoing) {
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
		WinScore = 0;
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

	void Draw_Cell_Text(int number, D2D1_RECT_F Rect);
	void Draw_Cell(int number, D2D1_RECT_F Rect);
	void Draw_Game(int x, int y, int width, int height);
	void Draw_Bet(int x, int y, int width, int height);
	void Draw_Function(int x, int y, int width, int height);
	// 檢測燈號
	bool isLight(std::map<int, bool> map, int number);
	int WinScore;
	int Score;
#endif

private:
	ID2D1Factory* m_pDirect2dFactory ;
	ID2D1HwndRenderTarget* m_pRenderTarget ;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;

	json BettingTable;


	int lightsecond = 200; //燈亮時間
	int lightIndex = 0;  

	std::map<int, int> Bet_call_map; //紀錄下注狀況  <號碼,金額>
	std::map<int, bool >Bet_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>
	std::map<int, bool> Game_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>
	std::map<int, bool> Compare_Light_map; //紀錄燈狀態 <號碼,燈亮或暗>

};
