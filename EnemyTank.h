#pragma once

#include "Tank.h"

class EnemyTank : public Tank
{
private:
	static bool m_IsCold;
	enum class STEP { MAX_STEP_TURN = 20, MAX_STEP_SHOOT = 15 };
	enum class TANKTYPE { HARD, MEDIUM, EASY };
	int m_TankType;

protected:
	void CalculateRegion();
	void DrawTank() const;
	void RandomTank();				//随机生成坦克信息
	void RandomDir(int type);		//随机生成坦克方向

public:
	EnemyTank() : Tank() { RandomTank(); }
	~EnemyTank() {}
	void Display() const;
	void Move();
	void Beaten();
	void Crash() { m_isCrashWithOther = true; }
	void noCrash() { m_isCrashWithOther = false; }
	static void Cold() { m_IsCold = true; }
	static bool IsCold() { return m_IsCold; }
	static void Release() { m_IsCold = false; }
};