#ifndef STATE_H
#define STATE_H


#include "Music.h"
#include <memory>
#include <vector>

class GameObject;

class State {
private:
	Music music;
	bool quitRequested;
	//std::vector<std::unique_ptr<GameObject>> objectArray;
	std::vector<std::shared_ptr<GameObject>> objectArray;

	void HandleInput(void);
	// void AddObject(int mouseX, int mouseY);

	bool started;
public:
	State (void);
	~State(void);
	bool QuitRequested (void);
	void LoadAssets (void);
	void Update (float);
	void Render (void);

	void UpdateObjects(float dt);
	void DetectCollisions(void);
	void EraseDeadObjects(void);

	void Start(void);
	std::weak_ptr<GameObject> AddObject(GameObject * go);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject * go) const;
};

#endif
