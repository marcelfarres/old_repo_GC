#include "box3f.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

box3f::box3f() {};

box3f::box3f(float r, float t, float f, float b, float l, float bk) :
	top(t), bottom(b),
	left(l), right(r),
	front(f), back(bk)
{};

box3f::~box3f(){
}

void box3f::render() const{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glVertex3f(left, top, front);
	glVertex3f(left, bottom, front);
	glVertex3f(right, bottom, front);
	glVertex3f(right, top, front);

	glVertex3f(right, top, front);
	glVertex3f(right, bottom, front);
	glVertex3f(right, bottom, back);
	glVertex3f(right, top, back);

	glVertex3f(right, top, back);
	glVertex3f(right, bottom, back);
	glVertex3f(left, bottom, back);
	glVertex3f(left, top, back);

	glVertex3f(left, top, back);
	glVertex3f(left, bottom, back);
	glVertex3f(left, bottom, front);
	glVertex3f(left, top, front);

	glEnd();
}

bool box3f::contains(const vector3f &v) const {
    return (left < v.x && v.x < right &&
            bottom < v.y && v.y < top &&
            back < v.z && v.z < front);
}
vector3f box3f::getCenter() const {
return vector3f((left + right)*0.5, (top + bottom)*0.5, (front + right)*0.5);
}
