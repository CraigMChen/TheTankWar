#pragma once

#include "Object.h"
#include "Food.h"

//治疗食物类
class CureFood : public Food
{
public:
	CureFood() : Food()
	{
		m_Color = LIGHTRED;
		m_Position.Set(rand() % 790, rand() % 550);
		CalculateRegion();
	}
	~CureFood() {}
};