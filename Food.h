#pragma once

#include "Object.h"

class Food : public Object
{
protected:
	void CalculateRegion();

public:
	Food() { m_IsDisappear = false; }
	~Food() {}
	void Fresh();
	virtual void Display() const;
	COLORREF GetColor() const { return m_Color; }
};