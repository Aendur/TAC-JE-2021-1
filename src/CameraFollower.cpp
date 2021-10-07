#include "CameraFollower.h"
#include "errors.h"

CameraFollower::CameraFollower (GameObject& go) : Component(go) {
	(void) go;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

// inherited from component
void CameraFollower::Update (float dt) {
	(void) dt;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void CameraFollower::Render (void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool CameraFollower::Is (const std::string & type) {
	(void) type;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
