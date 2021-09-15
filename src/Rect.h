#ifndef RECT_H
#define RECT_H

class Rect {
public:
	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float h = 0.0f;	

	Rect (void);
	bool Contains(float x, float y);
};

#endif
