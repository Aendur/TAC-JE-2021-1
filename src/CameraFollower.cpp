#include "CameraFollower.h"

#include "errors.h"
#include "GameObject.h"
#include "Camera.h"

CameraFollower::CameraFollower (GameObject& go) : Component(go) { }

// inherited from component
void CameraFollower::Update (float dt) {
	(void) dt;
	this->associated.box.x = Camera::pos.x;
	this->associated.box.y = Camera::pos.y;
}

void CameraFollower::Render (void) { }

bool CameraFollower::Is (const std::string & type) {
	return (type.compare("CameraFollower") == 0);
}
