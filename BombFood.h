#pragma once

#include "Food.h"

class BombFood : public Food
{
public:
	BombFood() : Food()
	{
		m_Color = WHITE;
		m_Position.Set(rand() % 790, rand() % 550);
		CalculateRegion();
	}
	~BombFood() {}
	void Display() const;
};