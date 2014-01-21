#include "box3f.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

box3f::box3f() {};

box3f::box3f(float r, float t, float f, float b, float l, float bk) :
    right(r), top(t), front(f),
    left(l), bottom(b), back(bk)
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

int box3f::get_octant(const vector3f &v) const {
    vector3f center = get_center();
    return ((v.x > center.x) << 2) |
           ((v.y > center.y) << 1) |
           (v.z > center.y);
}

vector3f box3f::get_center() const {
return vector3f((left + right)*0.5, (top + bottom)*0.5, (front + right)*0.5);
}

std::ostream& operator<<(std::ostream& os, const box3f& b) {
    os << "<box3f (";
    for (int i = 0; i < 5; i++) {
        os << b.coords[i] << ", ";
    }
   os << b.coords[5] << ")>\n"; 
   return os;
}
