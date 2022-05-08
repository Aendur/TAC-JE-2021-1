#include "Camera.h"
#include "GameObject.h"
#include "Vec2.h"
#include "errors.h"

#include <iostream>

void Camera::Follow(GameObject * newFocus) {
	focus = newFocus;
}

void Camera::Unfollow(void) {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if (focus != nullptr) {
		Vec2 center = focus->GetCenterPosition();
		pos.x = center.x - width / 2;
		pos.y = center.y - height / 2;
	} else {
		pos.x += speed.x * dt;
		pos.y += speed.y * dt;
	}
	//std::cout << "camera position: " << pos << " speed: " << speed << std::endl;
	//throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}




