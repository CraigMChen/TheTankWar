#pragma once

#include "Food.h"

//攻速食物类
class ShootSpeedFood : public Food
{
public:
	ShootSpeedFood() : Food()
	{
		m_Color = YELLOW;
		m_Position.Set(rand() % 790, rand() % 550);
		CalculateRegion();
	}
	~ShootSpeedFood() {}
};