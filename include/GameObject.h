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
	float angleDeg;

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
	
	float GetRotation(void);
	void SetRotation(float angle);

	void Start(void);

	Rect box;
};

#endif
