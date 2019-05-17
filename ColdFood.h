#pragma once

#include "Object.h"
#include "Food.h"
#include <ctime>

//冰冻食物类
class ColdFood : public Food
{
private:
	double m_ColdTimeBegin;		//冰冻开始时间
	double m_ColdTimeEnd;		//冰冻结束时间
	int m_ColdTime;

public:
	ColdFood();
	~ColdFood() {}
	void DrawColdFood();
	double GetDeltaTime() { return m_ColdTimeEnd - m_ColdTimeBegin; }
	void ColdBegin() { m_ColdTimeBegin = (double)time(0); }
	int GetColdTime () const{ return m_ColdTime; }
};