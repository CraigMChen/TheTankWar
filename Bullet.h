#pragma once

#include "Object.h"

class Bomb;

//�ӵ���
class Bullet : public Object
{
protected:
	void CalculateRegion();			//���㱬ը�뾶

public:
	Bullet();
	Bullet(Point pos, Dir dir, COLORREF color);
	~Bullet() {}

	void Display() const;
	void Move();
	void Boom(list<Bomb*> & listBombs);
};