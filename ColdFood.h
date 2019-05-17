#pragma once

#include "Object.h"
#include "Food.h"
#include <ctime>

//����ʳ����
class ColdFood : public Food
{
private:
	double m_ColdTimeBegin;		//������ʼʱ��
	double m_ColdTimeEnd;		//��������ʱ��
	int m_ColdTime;

public:
	ColdFood();
	~ColdFood() {}
	void DrawColdFood();
	double GetDeltaTime() { return m_ColdTimeEnd - m_ColdTimeBegin; }
	void ColdBegin() { m_ColdTimeBegin = (double)time(0); }
	int GetColdTime () const{ return m_ColdTime; }
};