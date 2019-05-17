#include "pch.h"
#include "BombFood.h"

void BombFood::Display() const
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setcolor(m_Color);
	setfillcolor(m_Color);

	fillcircle(m_Position.GetX(), m_Position.GetY(), 7);

	setcolor(RED);
	RECT r = { m_Position.GetX() - 7, m_Position.GetY() - 7, m_Position.GetX() + 7, m_Position.GetY() + 7 };
	drawtext(TCHAR('B'), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setcolor(color_save);
	setcolor(fill_color_save);
}