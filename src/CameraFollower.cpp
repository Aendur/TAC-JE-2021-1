#include "CameraFollower.h"

#include "errors.h"
#include "GameObject.h"
#include "Camera.h"

CameraFollower::CameraFollower (GameObject& go, const Vec2 & offset) : Component(go), offset(offset) { }

// inherited from component
void CameraFollower::Update (float dt) {
	(void) dt;
	this->associated.box.x = Camera::pos.x + offset.x;
	this->associated.box.y = Camera::pos.y + offset.y;
}

void CameraFollower::Render (void) { }

bool CameraFollower::Is (const std::string & type) const {
	return type.compare("CameraFollower") == 0;
}

const std::string CameraFollower::GetType(void) const {
	return "CameraFollower";
}