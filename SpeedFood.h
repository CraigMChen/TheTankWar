#pragma once

#include "Food.h"

//����ʳ����
class SpeedFood : public Food
{
public:
	SpeedFood()
	{
		m_Color = GREEN;
		m_Position.Set(rand() % 790, rand() % 550);
		CalculateRegion();
	}
	~SpeedFood() {}
};