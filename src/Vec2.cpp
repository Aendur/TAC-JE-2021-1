#include "Vec2.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Vec2 Vec2::RotateBy(float deg) const {
	double t = deg * M_PI / 180.0;
	double ct = cos(t);
	double st = sin(t);
	double rx = x * ct - y * st;
	double ry = y * ct + x * st;
	return Vec2((float)rx, (float)ry);
}

Vec2 Vec2::operator+(const Vec2 & other) const {
	return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(const Vec2 & other) const {
	return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator-(void) const {
	return Vec2(-this->x, -this->y);
}

Vec2 Vec2::operator*(float other) const {
	return Vec2(this->x * other, this->y * other);
}

Vec2 operator*(float op1, const Vec2 & op2) {
	return op2 * op1;
}

std::ostream& operator<< (std::ostream& os, const Vec2& vec) {
	os << '(' << vec.x << ',' << vec.y << ')';
	return os;
}
