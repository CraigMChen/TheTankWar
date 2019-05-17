#pragma once

//µ„¿‡
class Point
{
private:
	int m_x;
	int m_y;
public:
	Point(int x = 0, int y = 0) : m_x(x), m_y(y) {}
	~Point() {}
	Point & operator=(const Point & point)
	{
		m_x = point.m_x;
		m_y = point.m_y;
		return *this;
	}
	void Set(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; }
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
};