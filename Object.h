#pragma once

#include <list>
#include "Graphics.h"
using std::list;

//所有物品的基类
class Object
{
public:
	enum class Dir { UP, DOWN, LEFT, RIGHT };

protected:
	virtual void CalculateRegion() = 0;			//计算碰撞范围
	Dir m_Direction;
	Point m_Position;
	Rect m_RectSphere;							//碰撞范围
	int m_Speed;
	COLORREF m_Color;
	bool m_IsDisappear;

public:
	virtual void Display() const = 0;
	void SetDisappear() { m_IsDisappear = true; }
	bool IsDisappear() const { return m_IsDisappear; }
	const Rect & GetRegion() const { return m_RectSphere; }
};