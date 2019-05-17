#include "pch.h"
#include "EnemyTank.h"

bool EnemyTank::m_IsCold = false;

void EnemyTank::CalculateRegion()
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

void EnemyTank::DrawTank() const
{
	fillcircle(m_Position.GetX(), m_Position.GetY(), 6);
	switch (m_Direction)
	{
	case Dir::UP:
	case Dir::DOWN:
		fillrectangle(m_Position.GetX() - 13, m_Position.GetY() - 10, 
			m_Position.GetX() - 10, m_Position.GetY() + 10);
		fillrectangle(m_Position.GetX() + 10, m_Position.GetY() - 10, 
			m_Position.GetX() + 13, m_Position.GetY() + 10);
		break;
	case Dir::LEFT:
	case Dir::RIGHT:
		fillrectangle(m_Position.GetX() - 10, m_Position.GetY() + 13, 
			m_Position.GetX() + 10, m_Position.GetY() + 10);
		fillrectangle(m_Position.GetX() - 10, m_Position.GetY() - 10, 
			m_Position.GetX() + 10, m_Position.GetY() - 13);
		break;
	}
}

void EnemyTank::RandomTank()
{
	m_Position.SetX(rand() % (Graphics::GetBattleGround().GetWidth() - 30) + 15);
	m_Position.SetY(rand() % (Graphics::GetBattleGround().GatHeight() - 30) + 15);
	m_Direction = (Dir)((int)Dir::UP + rand() % 4);
	CalculateRegion();
	m_Speed = 2;
	m_StepCount = rand();
	m_isCrashWithOther = false;
	m_TankType = rand() % 3;
	switch (m_TankType)
	{
	case (int)TANKTYPE::EASY:
		m_Color = RED;
		m_Hp = 1;
		break;
	case (int)TANKTYPE::MEDIUM:
		m_Color = BLUE;
		m_Hp = 2;
		break;
	case (int)TANKTYPE::HARD:
		m_Color = RGB(128, 0, 128);
		m_Hp = 3;
		break;
	}
}

void EnemyTank::RandomDir(int type)
{
	//type为1时表示撞墙时改变方向
	//type为0时表示随机改变方向
	if (type)
	{
		Dir dir;
		while ((dir = Dir((int)Dir::UP + rand() % 4)) == m_Direction) {}
		m_Direction = dir;
	}
	else
		m_Direction = Dir((int)Dir::UP + rand() % 4);
}

void EnemyTank::Display() const
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

void EnemyTank::Move()
{
	if (m_isCrashWithOther)		//如果撞墙或撞到主坦克就掉头
	{
		if (m_Direction == Dir::UP) m_Direction = Dir::DOWN;
		if (m_Direction == Dir::DOWN) m_Direction = Dir::UP;
		if (m_Direction == Dir::LEFT) m_Direction = Dir::RIGHT;
		if (m_Direction == Dir::RIGHT) m_Direction = Dir::LEFT;
	}

	switch (m_Direction)
	{
	case Dir::UP:
		if (m_RectSphere.GetStartPoint().GetY() > Graphics::GetBattleGround().GetStartPoint().GetY() + 3)
			m_Position.SetY(m_Position.GetY() - m_Speed);
		else
			RandomDir(1);
		break;
	case Dir::DOWN:
		if (m_RectSphere.GetEndPoint().GetY() < Graphics::GetBattleGround().GetEndPoint().GetY() - 3)
			m_Position.SetY(m_Position.GetY() + m_Speed);
		else
			RandomDir(1);
		break;
	case Dir::LEFT:
		if (m_RectSphere.GetStartPoint().GetX() > Graphics::GetBattleGround().GetStartPoint().GetX() + 3)
			m_Position.SetX(m_Position.GetX() - m_Speed);
		else RandomDir(1);
		break;
	case Dir::RIGHT:
		if (m_RectSphere.GetEndPoint().GetX() < Graphics::GetBattleGround().GetEndPoint().GetX() - 3)
			m_Position.SetX(m_Position.GetX() + m_Speed);
		else RandomDir(1);
		break;
	}

	CalculateRegion();

	m_StepCount++;
	if (m_StepCount % (int)STEP::MAX_STEP_TURN == 0)
		RandomDir(0);
	if (m_StepCount % (int)STEP::MAX_STEP_SHOOT == 0)
		m_IsNeedShoot = true;
}

void EnemyTank::Beaten()
{
	m_Hp--;
	switch (m_Hp)
	{
	case 1:
		m_Color = RED;
		break;
	case 2:
		m_Color = BLUE;
		break;
	case 3:
		m_Color = RGB(128, 0, 128);
		break;
	default:
		break;
	}
	if (m_Hp == 0)
		SetDisappear();
}