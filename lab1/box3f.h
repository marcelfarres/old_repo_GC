#pragma once
#include "vector3f.h"
// Top is in the positive Y
// Right is positive X
// Front is positive Z

class box3f {
public:
	union {
		struct{ float coords[6]; };
		struct{ float right, top, front, left, bottom, back; };
	};

    box3f();
	box3f(float r, float t, float f, float l, float b, float bk);
	~box3f();
	void render() const;
    bool contains(const vector3f & v) const;
    vector3f getCenter() const;
};

