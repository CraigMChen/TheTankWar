#pragma once

class Setting
{
private:
	static int m_GameSpeed;		//��Ϸ�ٶ�
	static int m_Hp;			//����ֵ
	static int m_GameLevel;		//�ؿ��ȼ�
	static int m_TankNum;		//��ǰ̹������
	static int m_TotScore;		//�ܷ�
	static int m_KillScore;		//����̹�˵÷�
	static int m_KillNum;		//������̹����
	static int m_TankSpeed;		//��ǰ̹���ƶ��ٶ�
	static int m_TankShootSpeed;//��ǰ̹�˹����ٶ�
	static int m_Bombs;			//��ǰը����

public:
	static bool Restart;		//���¿�ʼ�ؿ����
	static bool NewLevel;		//�¹ؿ����
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