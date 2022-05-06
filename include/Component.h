#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component {
protected:
	GameObject & associated;
public:
	inline Component (GameObject & associated) : associated(associated) {}
	virtual ~Component () {}
	virtual void Update(float dt) = 0;
	virtual void Render(void) = 0;
	virtual bool Is(const std::string & type) = 0;
	virtual void Start(void) {}
};

#endif
