#include "Vec2.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Vec2 Vec2::RotateBy(float deg) {
	double t = deg * M_PI / 180.0;
	return Vec2((float)(x * cos(t) - y * sin(t)), (float)(y * cos(t) + x * sin(t)));
}

Vec2 Vec2::operator+(const Vec2 & other) {
	return Vec2(this->x + other.x, this->y + other.y);
}

std::ostream& operator<< (std::ostream& os, const Vec2& vec) {
	os << '(' << vec.x << ',' << vec.y << ')';
	return os;
}
