#include "Rect.h"

Rect::Rect (void) {}

bool Rect::Contains(float xi, float yi) {
	float x0 = this->x;
	float x1 = this->x + this->w;
	float y0 = this->y;
	float y1 = this->y + this->h;
	return (x0 <= xi && xi <= x1)
		&& (y0 <= yi && yi <= y1);
}