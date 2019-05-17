#pragma once

#include "Tank.h"
#include <ctime>

//��̹����
class MainTank : public Tank
{
private:
	int m_ShootSpeed;				//����
	int m_Bombs;					//ը����
	clock_t m_ShootBegin;			//�ϴ������ʼʱ��

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