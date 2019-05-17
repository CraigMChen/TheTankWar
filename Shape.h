#pragma once

#include "Rect.h"

//碰撞类
class Shape
{
private:
	static bool CheckPointInRec(const Point & point, const Rect & rect)		//检测点是否在矩形内
	{
		if (point.GetX() < rect.GetStartPoint().GetX() - 1 || point.GetX() > rect.GetEndPoint().GetX() + 1 ||
			point.GetY() < rect.GetStartPoint().GetY() - 1 || point.GetY() > rect.GetEndPoint().GetY() + 1)
			return false;
		return true;
	}
	//static bool CheckPointInRec(const Point & point, const Rect & rect)
	//{
	//	if (point.GetX() >= rect.GetStartPoint().GetX() && point.GetX() <= rect.GetEndPoint().GetX() &&
	//		point.GetY() >= rect.GetStartPoint().GetY() && point.GetY() <= rect.GetEndPoint().GetY())
	//		return true;
	//	return false;
	//}
public:
	static bool CheckIntersect(const Rect & rect1, const Rect & rect2)		//检测两个矩形是否碰撞
	{
		if (CheckPointInRec(rect1.GetStartPoint(), rect2) || CheckPointInRec(rect1.GetEndPoint(), rect2) ||
			CheckPointInRec(rect1.GetLeftPoint(), rect2) || CheckPointInRec(rect1.GetRightPoint(), rect2))
			return true;
		return false;
	}
};