#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <queue>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Vec2.h"

class Alien : public Component {
private:
	class Action {
		public:
		enum ActionType : int {
			MOVE,
			SHOOT,
		};

		ActionType type;
		Vec2 pos;
		Action(ActionType type, float x, float y) : type(type), pos(x, y) {}
	};

	Vec2 speed;
	int hp;
	int nMinions;
	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject>> minionArray;

	bool MoveTo(const Vec2 & newpos, float dt);
	bool ShootAt(const Vec2 & newpos);

public:
	//
	Alien (GameObject& associated, int nMinions);
	~Alien (void);

	// inherited from component
	void Start (void);
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
