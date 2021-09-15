#include "Rect.h"

Rect::Rect (void) {}

bool Rect::Contains(float x, float y) {
	float x0 = this->x;
	float x1 = this->x + this->w;
	float y0 = this->y;
	float y1 = this->y + this->h;
	return (x0 <= x && x <= x1)
		&& (y0 <= y && y <= y1);
}