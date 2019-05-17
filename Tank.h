#pragma once

#include <list>
#include "Object.h"
#include "Bullet.h"
#include "Bomb.h"
using std::list;

//坦克类
class Tank : public Object
{
protected:
	int m_Hp;
	virtual void CalculateRegion() = 0;
	virtual void DrawTank() const = 0;
	bool m_IsNeedShoot;
	bool m_isCrashWithOther;		//用于标记是否已经和其他坦克相撞
	int m_StepCount;				//记录步数

public:
	Tank()
	{
		m_IsDisappear = false;
		m_IsNeedShoot = false;
	}
	~Tank() {}
	virtual void Move() = 0;
	virtual void Beaten() = 0;
	void Boom(list<Bomb*> & listBombs)
	{
		listBombs.push_back(new Bomb(m_Position, (int)Bomb::BombType::LARGE, m_Color));
	}
	void Shoot(list<Bullet*> & listBullets)
	{
		listBullets.push_back(new Bullet(m_Position, m_Direction, m_Color));
		m_IsNeedShoot = false;
	}
	bool IsNeedShoot() const { return m_IsNeedShoot; }
	const Point & GetPosition() const { return m_Position; }
};