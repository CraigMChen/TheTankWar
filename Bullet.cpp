#include "pch.h"
#include "Bullet.h"
#include "Bomb.h"


void Bullet::CalculateRegion()
{
	m_RectSphere.SetRect(m_Position.GetX() - 2, m_Position.GetY() - 2,
		m_Position.GetX() + 2, m_Position.GetY() + 2);
}

Bullet::Bullet()
{
	m_Speed = 20;
	m_IsDisappear = false;
	CalculateRegion();
}

Bullet::Bullet(Point pos, Dir dir, COLORREF color) : Bullet()
{
	m_Position = pos;
	m_Direction = dir;
	m_Color = color;
}

void Bullet::Display() const
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_Color);
	setcolor(m_Color);
	fillcircle(m_Position.GetX(), m_Position.GetY(), 4);

	setfillcolor(fill_color_save);
	setcolor(color_save);
}

void Bullet::Move()
{
	switch (m_Direction)
	{
	case Dir::UP:
		m_Position.SetY(m_Position.GetY() - m_Speed);
		CalculateRegion();
		if (m_RectSphere.GetStartPoint().GetY() < Graphics::GetBattleGround().GetStartPoint().GetY())
		{
			m_Position.SetY(Graphics::GetBattleGround().GetStartPoint().GetY());
			m_IsDisappear = true;
		}
		break;
	case Dir::DOWN:
		m_Position.SetY(m_Position.GetY() + m_Speed);
		CalculateRegion();
		if (m_RectSphere.GetEndPoint().GetY() > Graphics::GetBattleGround().GetEndPoint().GetY())
		{
			m_Position.SetY(Graphics::GetBattleGround().GetEndPoint().GetY());
			m_IsDisappear = true;
		}
		break;
	case Dir::LEFT:
		m_Position.SetX(m_Position.GetX() - m_Speed);
		CalculateRegion();
		if (m_RectSphere.GetStartPoint().GetX() < Graphics::GetBattleGround().GetStartPoint().GetX())
		{
			m_Position.SetX(Graphics::GetBattleGround().GetStartPoint().GetX());
			m_IsDisappear = true;
		}
		break;
	case Dir::RIGHT:
		m_Position.SetX(m_Position.GetX() + m_Speed);
		CalculateRegion();
		if (m_RectSphere.GetEndPoint().GetX() > Graphics::GetBattleGround().GetEndPoint().GetX())
		{
			m_Position.SetX(Graphics::GetBattleGround().GetEndPoint().GetX());
			m_IsDisappear = true;
		}
		break;
	}
}

void Bullet::Boom(list<Bomb*> & listBombs)
{
	listBombs.push_back(new Bomb(m_Position, (int)Bomb::BombType::SMALL, m_Color));
}