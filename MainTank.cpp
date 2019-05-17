#include "pch.h"
#include "MainTank.h"
#include <ctime>

void MainTank::CalculateRegion()
{
	switch (m_Direction)
	{
	case Dir::UP:
	case Dir::DOWN:
		m_RectSphere.SetRect(m_Position.GetX() - 13, m_Position.GetY() - 10,
			m_Position.GetX() + 13, m_Position.GetY() + 10);
	case Dir::LEFT:
	case Dir::RIGHT:
		m_RectSphere.SetRect(m_Position.GetX() - 10, m_Position.GetY() - 13,
			m_Position.GetX() + 10, m_Position.GetY() + 13);
	}
}

void MainTank::DrawTank() const
{
	fillrectangle(m_Position.GetX() - 6, m_Position.GetY() - 6, m_Position.GetX() + 6, m_Position.GetY() + 6);
	switch (m_Direction)
	{
	case Dir::UP:
	case Dir::DOWN:
		fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetStartPoint().GetY(),
			m_RectSphere.GetStartPoint().GetX() + 2, m_RectSphere.GetEndPoint().GetY());
		fillrectangle(m_RectSphere.GetEndPoint().GetX() - 2, m_RectSphere.GetStartPoint().GetY(),
			m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetEndPoint().GetY());
		break;
	case Dir::LEFT:
	case Dir::RIGHT:
		fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetStartPoint().GetY(), 
			m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetStartPoint().GetY() + 2);
		fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetEndPoint().GetY() - 2,
			m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetEndPoint().GetY());
		break;
	}
}

void MainTank::Display() const
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_Color);
	setcolor(m_Color);

	DrawTank();

	switch (m_Direction)
	{
	case Dir::UP:
		line(m_Position.GetX(), m_Position.GetY(), m_Position.GetX(), m_Position.GetY() - 13);
		break;
	case Dir::DOWN:
		line(m_Position.GetX(), m_Position.GetY(), m_Position.GetX(), m_Position.GetY() + 13);
		break;
	case Dir::LEFT:
		line(m_Position.GetX(), m_Position.GetY(), m_Position.GetX() - 13, m_Position.GetY());
		break;
	case Dir::RIGHT:
		line(m_Position.GetX(), m_Position.GetY(), m_Position.GetX() + 13, m_Position.GetY());
		break;
	}
	
	setfillcolor(fill_color_save);
	setcolor(color_save);
}

MainTank::MainTank() : Tank()
{
	m_Hp = 20;
	m_Position.Set(300, 300);
	CalculateRegion();
	m_Color = YELLOW;
	m_Direction = Dir::UP;
	m_Speed = 2;
	m_ShootSpeed = 1000;
	m_isCrashWithOther = false;
	m_StepCount = rand();
	m_ShootBegin = clock();
}

void MainTank::Move()
{
	if (m_isCrashWithOther)
		return;
	switch (m_Direction)
	{
	case Dir::UP:
		if (m_RectSphere.GetStartPoint().GetY() > Graphics::GetBattleGround().GetStartPoint().GetY() + 3)
			m_Position.SetY(m_Position.GetY() - m_Speed);
		break;
	case Dir::DOWN:
		if (m_RectSphere.GetEndPoint().GetY() < Graphics::GetBattleGround().GetEndPoint().GetY() - 3)
			m_Position.SetY(m_Position.GetY() + m_Speed);
		break;
	case Dir::LEFT:
		if (m_RectSphere.GetStartPoint().GetX() > Graphics::GetBattleGround().GetStartPoint().GetX() + 3)
			m_Position.SetX(m_Position.GetX() - m_Speed);
		break;
	case Dir::RIGHT:
		if (m_RectSphere.GetEndPoint().GetX() < Graphics::GetBattleGround().GetEndPoint().GetX() - 3)
			m_Position.SetX(m_Position.GetX() + m_Speed);
		break;
	}

	CalculateRegion();
}

void MainTank::AddHp()
{
	m_Hp += 2;
	if (m_Hp > 20)
		m_Hp = 20;
}

void MainTank::MoveSpeedUp()
{
	m_Speed += 5;
	if (m_Speed > 20)
		m_Speed = 20;
}

void MainTank::ShootSpeedUp()
{
	m_ShootSpeed -= 100;
	if (m_ShootSpeed < 100)
		m_ShootSpeed = 100;
}

void MainTank::SpeedUp()
{
	m_Speed++;
	if (m_Speed > 10)
		m_Speed = 10;
}

void MainTank::Init()
{
	m_Hp = 20;
	m_ShootSpeed = 1000;
	m_Speed = 2;
	m_Bombs = 0;
}

bool MainTank::UseBomb()
{
	if (m_Bombs > 0)
	{
		m_Bombs--;
		return true;
	}
	return false;
}

void MainTank::GetShootTime()
{
	clock_t t = clock();
	if (t - m_ShootBegin > m_ShootSpeed)
	{
		m_IsNeedShoot = true;
		m_ShootBegin = t;
	}
}