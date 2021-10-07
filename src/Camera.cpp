#include "Camera.h"
#include "errors.h"

/*
private:
	inline static GameObject * focus = nullptr;
public:
	static Vec2 pos;
	static Vec2 speed;
*/

void Camera::Follow(GameObject * newFocus) {
	(void) newFocus;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void Camera::Unfollow(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void Camera::Update(float dt) {
	(void) dt;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}




