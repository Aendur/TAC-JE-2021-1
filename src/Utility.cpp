#include "Utility.h"
#include "Game.h"
//#include "GameObject.h"
//#include "Resources.h"
#include "Camera.h"
//#include <SDL2/SDL_image.h>
#include "Vec2.h"
#include "errors.h"

void Utility::DrawCircumference(const Vec2 & center, float radius, SDL_Color color) {
	static const int NPOINTS = 360;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_FPoint points[NPOINTS];
	for (int i = 0; i < NPOINTS; ++i) {
		Vec2 target = Vec2(radius, 0.0f).RotateBy(i * (360.0f / NPOINTS)) + center;
		points[i].x = target.x;
		points[i].y = target.y;
	}
	SDL_RenderDrawPointsF(Game::GetInstance().GetRenderer(), points, NPOINTS);
}

