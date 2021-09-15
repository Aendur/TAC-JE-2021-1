#include "Vec2.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Vec2::Vec2 (void) {}
Vec2::Vec2 (float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2 Vec2::RotateBy(float deg) {
	double t = deg * M_PI / 180.0;
	return Vec2(x * cos(t) - y * sin(t), y * cos(t) + x * sin(t));
}


Vec2 Vec2::operator+(const Vec2 & other) {
	return Vec2(this->x + other.x, this->y + other.y);
}
