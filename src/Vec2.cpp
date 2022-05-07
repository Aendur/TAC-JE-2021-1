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

float Vec2::mag(void) const {
	return std::sqrt(this->x * this->x + this->y * this->y);
}

float Vec2::deg(void) const {
	//return (float)(acos(this->x / this->mag()) * 180.0 / M_PI);
	return (float)(atan2(this->y, this->x) * 180.0 / M_PI);
}


Vec2 operator+(const Vec2 & op1, const Vec2 & op2) { return Vec2(op1.x + op2.x, op1.y + op2.y); }
Vec2 operator-(const Vec2 & op1, const Vec2 & op2) { return Vec2(op1.x - op2.x, op1.y - op2.y); }
Vec2 operator-(const Vec2 & op1)                   { return Vec2(-op1.x, -op1.y); }

Vec2  operator*(const Vec2 & op1,        float op2) { return Vec2(op1.x * op2, op1.y * op2); }
Vec2  operator*(float        op1, const Vec2 & op2) { return op2 * op1; }
float operator*(const Vec2 & op1, const Vec2 & op2) { return op1.x * op2.x + op1.y * op2.y; }

//float operator%(const Vec2 & op1, const Vec2 & op2) { return acosf(op1 * op2) / (op1.mag() * op2.mag()); }
//float operator%(const Vec2 & op1, const Vec2 & op2) { return acosf(op1 * op2) / (op1.mag() * op2.mag()); }

bool operator<(const Vec2 & op1, float op2) { return op1.mag() < op2; }
bool operator<(float op1, const Vec2 & op2) { return op1 < op2.mag(); }

std::ostream& operator<< (std::ostream& os, const Vec2& vec) {
	os << '(' << vec.x << ',' << vec.y << ')';
	return os;
}

