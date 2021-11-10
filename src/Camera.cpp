#include "Camera.h"
#include "errors.h"

#include <iostream>
/*
private:
	inline static GameObject * focus = nullptr;
public:
	static Vec2 pos;
	static Vec2 speed;
*/

void Camera::Follow(GameObject * newFocus) {
	focus = newFocus;
}

void Camera::Unfollow(void) {
	focus = nullptr;
}

void Camera::Update(float dt) {
	pos.x += speed.x * dt;
	pos.y += speed.y * dt;
	//std::cout << "camera position: " << pos << " speed: " << speed << std::endl;
	//throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}




