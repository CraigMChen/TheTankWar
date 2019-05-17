#include "pch.h"
#include <conio.h>
#include "Graphics.h"
#include "Setting.h"
#include <iostream>
#include <string.h>
#include "mmsystem.h"
#include <Windows.h>
#include "resource.h"
#pragma comment(lib,"winmm.lib")

Rect Graphics::m_RectBattleGround;
Rect Graphics::m_RectScreen;
char Graphics::m_pArray[100];

void Graphics::DrawBattleGround()
{
	COLORREF color_save = getcolor();
	setcolor(BLUE);
	rectangle(
		m_RectBattleGround.GetStartPoint().GetX(), 
		m_RectBattleGround.GetStartPoint().GetY(),
		m_RectBattleGround.GetEndPoint().GetX(), 
		m_RectBattleGround.GetEndPoint().GetY()
	);
	setcolor(color_save);
}

void Graphics::Create()
{
	m_RectScreen.SetRect(0, 0, 
		(int)Graphics::SCREEN::SCREEN_WIDTH, 
		(int)Graphics::SCREEN::SCREEN_HEIGHT
	);
	initgraph((int)Graphics::SCREEN::SCREEN_WIDTH, 
		(int)Graphics::SCREEN::SCREEN_HEIGHT);
	setbkcolor(RGB(0, 0, 0));
	m_RectBattleGround.SetRect(
		(int)Graphics::BATTLE_GROUND::BATTLE_GROUND_X1,
		(int)Graphics::BATTLE_GROUND::BATTLE_GROUND_Y1,
		(int)Graphics::BATTLE_GROUND::BATTLE_GROUND_X2,
		(int)Graphics::BATTLE_GROUND::BATTLE_GROUND_Y2
	);
}

void Graphics::Destory()
{
	closegraph();
}

void Graphics::ShowScore()
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setcolor(RGB(255, 215, 0));

	LOGFONT font_save;
	gettextstyle(&font_save);
	LOGFONT fontstyle;
	gettextstyle(&fontstyle);
	fontstyle.lfHeight = 32;
	_tcscpy_s(fontstyle.lfFaceName, _T("Rosewood Std Regular"));
	fontstyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&fontstyle);

	rectangle(
		(int)Graphics::SCORE::SCORE_LEFT,
		(int)Graphics::SCORE::SCORE_TOP,
		(int)Graphics::SCORE::SCORE_LEFT +200,
		(int)Graphics::SCORE::SCORE_TOP + 40
	);
	RECT r =
	{
		(int)Graphics::SCORE::SCORE_LEFT,
		(int)Graphics::SCORE::SCORE_TOP,
		(int)Graphics::SCORE::SCORE_LEFT + 200,
		(int)Graphics::SCORE::SCORE_TOP + 40
	};

	wsprintf((LPWSTR)m_pArray, _T("LEVEL %d"), Setting::GetGameLevel());
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	fontstyle.lfHeight = 20;
	_tcscpy_s(fontstyle.lfFaceName, _T("方正姚体"));
	settextstyle(&fontstyle);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("总分：%d"), Setting::GetTotScore());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("生命：%d"), Setting::GetHp());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("敌人数量：%d"), Setting::GetTankNum());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("击毁敌人数量：%d"), Setting::GetKillNum());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("坦克移动速度：%d"), Setting::GetTankSpeed());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("坦克攻击速度：%d"), Setting::GetTankShootSpeed());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("剩余炸弹数：%d"), Setting::GetBombs());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	setcolor(color_save);
	setfillcolor(fill_color_save);
	settextstyle(&font_save);
}

void Graphics::Help()
{
	cleardevice();

	LOGFONT font_save;
	gettextstyle(&font_save);
	LOGFONT fontstyle;
	gettextstyle(&fontstyle);
	fontstyle.lfHeight = 72;
	_tcscpy_s(fontstyle.lfFaceName, _T("方正姚体"));
	fontstyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&fontstyle);

	RECT title = { 0, 0, 1024, 100 };
	wsprintf((LPWSTR)m_pArray, _T("游戏帮助"));
	drawtext((LPWSTR)m_pArray, &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	fontstyle.lfHeight = 48;
	settextstyle(&fontstyle);
	RECT r = { 0, 150, (int)SCREEN::SCREEN_WIDTH, 200 };
	wsprintf((LPWSTR)m_pArray, _T("方向键控制坦克移动"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("回车键暂停游戏"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("粉红色食物可以回血"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("蓝色食物可以冻结敌人8秒"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("绿色食物可以加快移动速度"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("蓝色食物可以加快攻击速度"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("按任意键返回"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextstyle(&font_save);
	_getch();
	cleardevice();
}

void Graphics::Menu()
{
	PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	RECT title = { 0, 0, 1024, 200 };
	RECT menu1 = { 0, 250, 1024, 300 };
	RECT menu2 = { 0, 350, 1024, 400 };
	RECT menu3 = { 0, 450, 1024, 500 };
	RECT menu4 = { 0, 0, 1024, 568 };
	int select = 1;

	while (true)
	{	
		setcolor(YELLOW);
		LOGFONT font_save;
		gettextstyle(&font_save);
		LOGFONT fontstyle;
		gettextstyle(&fontstyle);
		fontstyle.lfHeight = 72;
		_tcscpy_s(fontstyle.lfFaceName, _T("Rosewood Std Regular"));
		fontstyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&fontstyle);
		wsprintf((LPWSTR)m_pArray, _T("*The Tank War*"));
		drawtext((LPWSTR)m_pArray, &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		fontstyle.lfHeight = 48;
		_tcscpy_s(fontstyle.lfFaceName, _T("方正姚体"));
		settextstyle(&fontstyle);
		wsprintf((LPWSTR)m_pArray, _T("%c开始游戏%c"), (select == 1 ? '>' : ' '), (select == 1 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c游戏帮助%c"), (select == 2 ? '>' : ' '), (select == 2 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c退出游戏%c"), (select == 3 ? '>' : ' '), (select == 3 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu3, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		fontstyle.lfHeight = 16;
		settextstyle(&fontstyle);
		wsprintf((LPWSTR)m_pArray, _T("作者：CMC，版本：2.0"));
		drawtext((LPWSTR)m_pArray, &menu4, DT_BOTTOM | DT_SINGLELINE | DT_RIGHT);

		settextstyle(&font_save);

		if (_kbhit())
		{
			PlaySound(LPWSTR(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			cleardevice();
			int key = _getch();
			switch (key)
			{
			case 72:
				select--;
				if (select < 1)
					select = 3;
				break;
			case 80:
				select++;
				if (select > 3)
					select = 1;
				break;
			case 13:
				if (select == 1)
				{
					cleardevice();
					return;
				}
				if (select == 2)
					Help();
				if (select == 3)
					exit(1);
				break;
			default:
				break;
			}
		}
	}
}

int Graphics::GameOver(const Point & pos)
{
	PlaySound(LPWSTR(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();
	COLORREF bkcolor_save = getbkcolor();

	setfillcolor(RED);
	setcolor(RED);
	int region = 1;
	while (region <= 1171)
	{
		fillcircle(pos.GetX(), pos.GetY(), region);
		region += 10;
		Sleep(10);
	}
	PlaySound(LPWSTR(IDR_WAVE7), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
	setbkcolor(RED);
	cleardevice();
	RECT title = { 0, 0, 1024, 100 };
	RECT gameinfo = { 0, 150, 1024, 200 };
	RECT menu1 = { 0, 250, 1024, 300 };
	RECT menu2 = { 0, 350, 1024, 400 };
	RECT menu3 = { 0, 450, 1024, 500 };

	int select = 1;

	while (true)
	{
		setcolor(YELLOW);

		LOGFONT font_save;
		gettextstyle(&font_save);
		LOGFONT fontstyle;
		gettextstyle(&fontstyle);
		fontstyle.lfHeight = 56;
		_tcscpy_s(fontstyle.lfFaceName, _T("方正姚体"));
		fontstyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&fontstyle);

		wsprintf((LPWSTR)m_pArray, _T("游戏结束，坦克被摧毁"));
		drawtext((LPWSTR)m_pArray, &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("最终得分：%d"), Setting::GetTotScore());
		drawtext((LPWSTR)m_pArray, &gameinfo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c重新开始本关%c"), (select == 1 ? '>' : ' '), (select == 1 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c返回主菜单%c"), (select == 2 ? '>' : ' '), (select == 2 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c退出游戏%c"), (select == 3 ? '>' : ' '), (select == 3 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu3, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		settextstyle(&font_save);

		if (_kbhit())
		{
			PlaySound(LPWSTR(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			cleardevice();
			int key = _getch();
			switch (key)
			{
			case 72:
				select--;
				if (select < 1)
					select = 3;
				break;
			case 80:
				select++;
				if (select > 3)
					select = 1;
				break;
			case 13:
				setfillcolor(fill_color_save);
				setcolor(color_save);
				setbkcolor(bkcolor_save);
				cleardevice();
				return select;
			default:
				break;
			}
		}
	}
}