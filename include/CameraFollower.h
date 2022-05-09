#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "Component.h"
#include "Vec2.h"

class CameraFollower : public Component {
private:
	Vec2 offset;
public:
	//
	CameraFollower (GameObject& go, const Vec2 & offset = {0,0});

	inline void SetOffest(const Vec2 & value) { offset = value; }

	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
