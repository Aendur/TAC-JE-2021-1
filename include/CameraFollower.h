#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "Component.h"

class CameraFollower : public Component {
private:
public:
	//
	CameraFollower (GameObject& go);

	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
