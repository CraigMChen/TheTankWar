#include "pch.h"
#include "Setting.h"

int Setting::m_GameSpeed = 60;
bool Setting::NewLevel = true;
bool Setting::Restart = false;
int Setting::m_Hp = 20;
int Setting::m_GameLevel = 0;
int Setting::m_TankNum = 5;
int Setting::m_TotScore = 0;
int Setting::m_KillScore = 5;
int Setting::m_KillNum = 0;
int Setting::m_TankSpeed = 2;
int Setting::m_TankShootSpeed = 15;
int Setting::m_Bombs = 0;

void Setting::NewGameLevel()
{
	m_Hp = 20;
	m_GameLevel++;
	m_TankNum = 10 + 5 * (m_GameLevel - 1);
	m_KillScore += 5;
}

void Setting::Damaged()
{

	m_TankNum--;
	m_TotScore += m_KillScore;
	m_KillNum++;
	if (m_TankNum == 0) NewLevel = true;
}

void Setting::SetInfo(int TotScore, int KillNum, int TankNum)
{
	m_TotScore = TotScore;
	m_KillNum = KillNum;
	m_TankNum = TankNum;
}

void Setting::Init()
{
	m_GameSpeed = 60;
	NewLevel = true;
	Restart = false;
	m_Hp = 20;
	m_GameLevel = 0;
	m_TankNum = 5;
	m_TotScore = 0;
	m_KillScore = 5;
	m_KillNum = 0;
	m_Bombs = 0;
}