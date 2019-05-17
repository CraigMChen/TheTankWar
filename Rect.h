#pragma once

#include "Point.h"

//矩形类
class Rect
{
private:
	Point m_StartPoint;		//左上角的顶点
	Point m_EndPoint;		//右下角的顶点
public:
	Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : m_StartPoint(x1, y1), m_EndPoint(x2, y2) {}
	Rect(Point StartPoint, Point EndPoint) : m_StartPoint(StartPoint), m_EndPoint(EndPoint) {}
	Rect(Rect & Rt) : m_StartPoint(Rt.m_StartPoint), m_EndPoint(Rt.m_EndPoint) {}
	~Rect() {}
	void SetRect(int x1, int y1, int x2, int y2)
	{
		m_StartPoint.Set(x1, y1);
		m_EndPoint.Set(x2, y2);
	}
	void SetRect(Point StartPoint, Point EndPoint)
	{
		m_StartPoint = StartPoint;
		m_EndPoint = EndPoint;
	}
	void SetStartPoint(Point StartPoint) { m_StartPoint = StartPoint; }
	void SetEndPoint(Point EndPoint) { m_EndPoint = EndPoint; }
	Point GetStartPoint() const { return m_StartPoint; }
	Point GetEndPoint() const { return m_EndPoint; }
	Point GetRightPoint() const
	{
		return Point(m_EndPoint.GetX(), m_StartPoint.GetY());
	}
	Point GetLeftPoint() const
	{
		return Point(m_StartPoint.GetX(), m_EndPoint.GetY());
	}
	Rect & operator=(const Rect & Rt)
	{
		m_StartPoint = Rt.m_StartPoint;
		m_EndPoint = Rt.m_EndPoint;
		return *this;
	}
	int GetWidth() const { return m_EndPoint.GetX() - m_StartPoint.GetX(); }		//返回矩形长
	int GatHeight() const { return m_EndPoint.GetY() - m_StartPoint.GetY(); }		//返回矩形宽
};