#ifndef CAMERA_H
#define CAMERA_H

#include "Vec2.h"

class GameObject;
class Camera {
private:
	inline static GameObject * focus = nullptr;

public:
	static Vec2 pos;
	static Vec2 speed;

	static void Follow(GameObject * newFocus);
	static void Unfollow(void);
	static void Update(float dt);
};

#endif
