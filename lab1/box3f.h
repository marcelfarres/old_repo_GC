#pragma once
#include "vector3f.h"
class box3f
{
public:
	box3f(float t, float b, float l, float r, float f, float bk);
	~box3f();
	void render() const;

private: 
	union {
		struct{ float coords[6]; };
		struct{ float top, bottom, left, right, front, back; };
	};

};

