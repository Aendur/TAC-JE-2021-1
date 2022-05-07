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
	Vec2 operator+(const Vec2 & other) const;
	Vec2 operator-(const Vec2 & other) const;
	Vec2 operator-(void) const;
	Vec2 operator*(float other) const;

	friend std::ostream& operator<< (std::ostream&, const Vec2&);
};

Vec2 operator*(float op1, const Vec2 & op2);


#endif
