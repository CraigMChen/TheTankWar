#pragma once

#include "Object.h"
#include "Food.h"

//����ʳ����
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