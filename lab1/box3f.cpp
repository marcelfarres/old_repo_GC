#include "box3f.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

box3f::box3f(float t, float b, float l, float r, float f, float bk) :
	top(t), bottom(b),
	left(l), right(r),
	front(f), back(bk)
{};

box3f::~box3f(){
}

void box3f::render() const{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);

	glVertex3f(top, left, front);
	glVertex3f(bottom, left, front);
	glVertex3f(bottom, right, front);
	glVertex3f(top, right, front);

	glVertex3f(top, right, front);
	glVertex3f(bottom, right, front);
	glVertex3f(bottom, right, back);
	glVertex3f(top, right, back);

	glVertex3f(top, right, back);
	glVertex3f(bottom, right, back);
	glVertex3f(bottom, left, back);
	glVertex3f(top, left, back);

	glVertex3f(top, left, back);
	glVertex3f(bottom, left, back);
	glVertex3f(bottom, left, front);
	glVertex3f(top, left, front);

	glEnd();

}
