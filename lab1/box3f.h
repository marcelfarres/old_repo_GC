#pragma once
#include "vector3f.h"
class box3f
{
public:
	box3f(int t, int b, int l, int r, int f, int bk);
	~box3f();
	void render() const;

private: 
	union {
		struct{ float coords[6]; };
		struct{ float top, bottom, left, right, front, back; };
	};

};

