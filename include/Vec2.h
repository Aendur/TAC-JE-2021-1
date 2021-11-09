#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
	float x = 0.0f;
	float y = 0.0f;
	
	Vec2 (void);
	Vec2 (float x, float y);
	
	Vec2 RotateBy(float deg);
	Vec2 operator+(const Vec2 & other);
};

#endif
