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
	_tcscpy_s(fontstyle.lfFaceName, _T("����Ҧ��"));
	settextstyle(&fontstyle);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("�ܷ֣�%d"), Setting::GetTotScore());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("������%d"), Setting::GetHp());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("����������%d"), Setting::GetTankNum());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("���ٵ���������%d"), Setting::GetKillNum());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("̹���ƶ��ٶȣ�%d"), Setting::GetTankSpeed());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("̹�˹����ٶȣ�%d"), Setting::GetTankShootSpeed());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("ʣ��ը������%d"), Setting::GetBombs());
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
	_tcscpy_s(fontstyle.lfFaceName, _T("����Ҧ��"));
	fontstyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&fontstyle);

	RECT title = { 0, 0, 1024, 100 };
	wsprintf((LPWSTR)m_pArray, _T("��Ϸ����"));
	drawtext((LPWSTR)m_pArray, &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	fontstyle.lfHeight = 48;
	settextstyle(&fontstyle);
	RECT r = { 0, 150, (int)SCREEN::SCREEN_WIDTH, 200 };
	wsprintf((LPWSTR)m_pArray, _T("���������̹���ƶ�"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("�س�����ͣ��Ϸ"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("�ۺ�ɫʳ����Ի�Ѫ"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("��ɫʳ����Զ������8��"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("��ɫʳ����Լӿ��ƶ��ٶ�"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("��ɫʳ����Լӿ칥���ٶ�"));
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50; r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("�����������"));
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
		_tcscpy_s(fontstyle.lfFaceName, _T("����Ҧ��"));
		settextstyle(&fontstyle);
		wsprintf((LPWSTR)m_pArray, _T("%c��ʼ��Ϸ%c"), (select == 1 ? '>' : ' '), (select == 1 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c��Ϸ����%c"), (select == 2 ? '>' : ' '), (select == 2 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c�˳���Ϸ%c"), (select == 3 ? '>' : ' '), (select == 3 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu3, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		fontstyle.lfHeight = 16;
		settextstyle(&fontstyle);
		wsprintf((LPWSTR)m_pArray, _T("���ߣ�CMC���汾��2.0"));
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
		_tcscpy_s(fontstyle.lfFaceName, _T("����Ҧ��"));
		fontstyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&fontstyle);

		wsprintf((LPWSTR)m_pArray, _T("��Ϸ������̹�˱��ݻ�"));
		drawtext((LPWSTR)m_pArray, &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("���յ÷֣�%d"), Setting::GetTotScore());
		drawtext((LPWSTR)m_pArray, &gameinfo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c���¿�ʼ����%c"), (select == 1 ? '>' : ' '), (select == 1 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c�������˵�%c"), (select == 2 ? '>' : ' '), (select == 2 ? '<' : ' '));
		drawtext((LPWSTR)m_pArray, &menu2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		wsprintf((LPWSTR)m_pArray, _T("%c�˳���Ϸ%c"), (select == 3 ? '>' : ' '), (select == 3 ? '<' : ' '));
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