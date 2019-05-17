#include "pch.h"
#include "ColdFood.h"

ColdFood::ColdFood() : Food()
{
	m_Color = LIGHTBLUE;
	m_ColdTime = 0;
	m_ColdTimeBegin = 0;
	m_ColdTimeEnd = 0;
	m_Position.Set(rand() % 790, rand() % 550);
	CalculateRegion();
}

void ColdFood::DrawColdFood()
{
	Display();
	m_ColdTimeEnd = (double)time(0);
}