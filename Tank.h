#pragma once

#include <list>
#include "Object.h"
#include "Bullet.h"
#include "Bomb.h"
using std::list;

//̹����
class Tank : public Object
{
protected:
	int m_Hp;
	virtual void CalculateRegion() = 0;
	virtual void DrawTank() const = 0;
	bool m_IsNeedShoot;
	bool m_isCrashWithOther;		//���ڱ���Ƿ��Ѿ�������̹����ײ
	int m_StepCount;				//��¼����

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