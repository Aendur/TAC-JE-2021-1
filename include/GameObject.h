#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "Rect.h"
#include "Vec2.h"
class Component;

class GameObject {
private:
	std::vector<Component*> components;
	bool isDead;
	bool started; 
	float rot;

public:
	GameObject (void);
	~GameObject (void);
	void Update(float dt);
	void Render(void);
	bool IsDead(void);
	void RequestDelete(void);
	void AddComponent(Component * cpt);
	void RemoveComponent(Component * cpt);
	Component * GetComponent(const std::string & type);

	Vec2 GetPosition(void) const;
	Vec2 GetCenterPosition(void) const;
	void SetPosition(const Vec2 & pos);
	void SetCenterPosition(const Vec2 & pos);
	
	float GetRotation(void); // { return rot; }
	void SetRotation(float angle); // { rot = angle; if (rot < 0.0f) rot = 0.0f; if (rot > 360.0f) rot = 360.0f; }

	void Start(void);

	Rect box;
};

#endif
