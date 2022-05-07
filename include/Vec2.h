#ifndef VEC2_H
#define VEC2_H

#include <ostream>

class Vec2 {
public:
	float x = 0.0f;
	float y = 0.0f;
	
	Vec2 (void) : x(0.0f), y(0.0f) {}
	Vec2 (float x, float y) : x(x), y(y) {}
	
	Vec2 RotateBy(float deg) const;
	float mag(void) const;
	float deg(void) const;
};

Vec2 operator+(const Vec2 & op1, const Vec2 & op2);
Vec2 operator-(const Vec2 & op1, const Vec2 & op2);
Vec2 operator-(const Vec2 & op1);

Vec2 operator*(const Vec2 & op1, float op2);
Vec2 operator*(float op1, const Vec2 & op2);
float operator*(const Vec2 & op1, const Vec2 & op2);

float operator%(const Vec2 & op1, const Vec2 & op2);

bool operator<(const Vec2 & op1, float op2);
bool operator<(float op1, const Vec2 & op2);

std::ostream& operator<< (std::ostream&, const Vec2&);


#endif
