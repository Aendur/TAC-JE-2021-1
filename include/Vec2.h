#ifndef VEC2_H
#define VEC2_H

#include <ostream>

class Vec2 {
public:
	float x = 0.0f;
	float y = 0.0f;
	
	Vec2 (void) : x(0.0f), y(0.0f) {}
	Vec2 (float x, float y) : x(x), y(y) {}
	
	Vec2 RotateBy(float deg);
	Vec2 operator+(const Vec2 & other);

	friend std::ostream& operator<< (std::ostream&, const Vec2&);
};


#endif
