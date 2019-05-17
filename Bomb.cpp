#include "pch.h"
#include "Bomb.h"

Bomb::Bomb()
{
	m_IsDisappear = false;
	m_Color = YELLOW;
	m_Direction = Dir::UP;
	m_Region = 0;
}

Bomb::Bomb(Point pos, int maxregion, COLORREF color) : Bomb()
{
	m_Position = pos;
	m_MaxRegion = maxregion;
	m_Color = color;
}

void Bomb::Display() const
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_Color);
	setcolor(m_Color);
	fillcircle(m_Position.GetX(), m_Position.GetY(), m_Region);

	setfillcolor(fill_color_save);
	setcolor(color_save);
}

void Bomb::Move()
{
	m_Region += 2;
	if (m_Region >= m_MaxRegion)
		m_IsDisappear = true;
}
