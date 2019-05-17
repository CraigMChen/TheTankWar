#pragma once

#include "Object.h"

class Bomb;

//×Óµ¯Àà
class Bullet : public Object
{
protected:
	void CalculateRegion();			//¼ÆËã±¬Õ¨°ë¾¶

public:
	Bullet();
	Bullet(Point pos, Dir dir, COLORREF color);
	~Bullet() {}

	void Display() const;
	void Move();
	void Boom(list<Bomb*> & listBombs);
};