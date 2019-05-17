#pragma once

#include <graphics.h>
#include "Rect.h"

class Graphics
{
private:
	static Rect m_RectBattleGround;
	static Rect m_RectScreen;
	static char m_pArray[100];

public:
	enum class SCREEN
	{
		SCREEN_WIDTH = 1024,
		SCREEN_HEIGHT = 568
	};
	enum class BATTLE_GROUND
	{
		BATTLE_GROUND_X1 = 5,
		BATTLE_GROUND_Y1 = 5,
		BATTLE_GROUND_X2 = 800,
		BATTLE_GROUND_Y2 = (int(SCREEN::SCREEN_HEIGHT) - BATTLE_GROUND_Y1)
	};
	enum class SCORE
	{
		SCORE_LEFT = 810,
		SCORE_TOP = 5
	};
	static void DrawBattleGround();
	static void Create();
	static void Destory();
	static void ShowScore();
	static int GetScreenWidth() { return (int)SCREEN::SCREEN_WIDTH; }
	static int GetScreenHeight() { return (int)SCREEN::SCREEN_HEIGHT; }
	static Rect GetBattleGround() { return m_RectBattleGround; }
	static void Menu();
	static void Help();
	static int GameOver(const Point & pos);
};