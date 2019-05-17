#pragma once

class Setting
{
private:
	static int m_GameSpeed;		//游戏速度
	static int m_Hp;			//生命值
	static int m_GameLevel;		//关卡等级
	static int m_TankNum;		//当前坦克数量
	static int m_TotScore;		//总分
	static int m_KillScore;		//击毁坦克得分
	static int m_KillNum;		//共击毁坦克数
	static int m_TankSpeed;		//当前坦克移动速度
	static int m_TankShootSpeed;//当前坦克攻击速度
	static int m_Bombs;			//当前炸弹数

public:
	static bool Restart;		//重新开始关卡标记
	static bool NewLevel;		//新关卡标记
	static int GetGameSpeed() { return m_GameSpeed; }
	static int GetHp() { return m_Hp; }
	static int GetGameLevel() { return m_GameLevel; }
	static int GetTankNum() { return m_TankNum; }
	static int GetTotScore() { return m_TotScore; }
	static int GetKillScore() { return m_KillScore; }
	static int GetKillNum() { return m_KillNum; }
	static int GetTankSpeed() { return m_TankSpeed; }
	static int GetTankShootSpeed() { return m_TankShootSpeed; }
	static int GetBombs() { return m_Bombs; }
	static void NewGameLevel();
	static void Damaged();
	static void SetInfo(int TotScore, int KillNum, int TankNum);
	static void Init();
	static void SetTankInfo(int hp, int speed, int shootspeed, int bombs)
	{
		m_Hp = hp;
		m_TankSpeed = speed;
		m_TankShootSpeed = shootspeed;
		m_Bombs = bombs;
	}
};