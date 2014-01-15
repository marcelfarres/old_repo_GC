#pragma once
#include "vector3f.h"
class box3f
{
public:
	box3f(int t, int b, int l, int r, int f, int bk) :
		top(t), bottom(b),
		left(l), right(r),
		front(f), back(bk)
		{};
	~box3f();

private: 
	float top, bottom;
	float left, right;
	float front, back;

};

