#ifndef CAMERA_H
#define CAMERA_H

#include "Vec2.h"

class GameObject;
class Camera {
private:
	inline static GameObject * focus = nullptr;

public:
	inline static Vec2 pos = {0.0f, 0.0f};
	inline static Vec2 speed = {0.0f, 0.0f};
	inline static int width = 0;
	inline static int height = 0;

	static void Follow(GameObject * newFocus);
	static void Unfollow(void);
	static void Update(float dt);
};

#endif
