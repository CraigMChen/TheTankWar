#pragma once

#include "Object.h"

//±¨’®¿‡
class Bomb : public Object
{
public:
	enum class BombType { HUGE = 72, LARGE = 12, SMALL = 8 };

protected:
	void CalculateRegion() {}
	int m_MaxRegion;
	int m_Region;

public:
	Bomb();
	Bomb(Point pos, int maxregion, COLORREF color);
	~Bomb() {}
	void Display() const;
	void Move();
};