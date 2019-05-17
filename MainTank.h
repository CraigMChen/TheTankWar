#pragma once

#include "Tank.h"
#include <ctime>

//主坦克类
class MainTank : public Tank
{
private:
	int m_ShootSpeed;				//攻速
	int m_Bombs;					//炸弹数
	clock_t m_ShootBegin;			//上次射击开始时间

protected:
	void CalculateRegion();
	void DrawTank() const;

public:
	MainTank();
	~MainTank() {}
	void Display() const;
	void Move();
	void AddHp();
	void AddBombs() { m_Bombs++; }
	void SetDir(Dir dir) { m_Direction = dir; }
	void Beaten() { m_Hp--; }
	int GetHp() const { return m_Hp; }
	int GetSpeed() const { return m_Speed; }
	int GetShootSpeed() const { return m_ShootSpeed; }
	int GetDir() const { return (int)m_Direction; }
	int GetBombs() const { return m_Bombs; }
	void Crash() { m_isCrashWithOther = true; }
	void noCrash() { m_isCrashWithOther = false; }
	const Point & GetPosition() const { return m_Position; }
	void MoveSpeedUp();
	void ShootSpeedUp();
	void SpeedUp();
	void Init();
	bool UseBomb();
	void GetShootTime();
};