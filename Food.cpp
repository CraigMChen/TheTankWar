#include "pch.h"
#include "Food.h"
#include <ctime>

void Food::CalculateRegion()
{
	m_RectSphere.SetRect(m_Position.GetX() - 7, m_Position.GetY() - 7,
	m_Position.GetX() + 7, m_Position.GetY() + 7);
}

void Food::Fresh()
{
	m_Position.Set(rand() % 790, rand() % 550);
	CalculateRegion();
}

void Food::Display() const
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setcolor(m_Color);
	setfillcolor(m_Color);

	fillcircle(m_Position.GetX(), m_Position.GetY(), 7);

	setcolor(color_save);
	setcolor(fill_color_save);
}