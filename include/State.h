#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>

class GameObject;
class State {
protected:
	void StartArray(void);
	void UpdateArray(float dt);
	void RenderArray(void);

	bool popRequested = false;
	bool quitRequested = false;
	bool started = false;
	std::vector<std::shared_ptr<GameObject>> objectArray;

public:
	State (void) {}
	virtual ~State(void);
	virtual void LoadAssets (void) = 0;
	virtual void Update (float) = 0;
	virtual void Render (void) = 0;
	virtual void Start(void) = 0;
	virtual void Pause(void) = 0;
	virtual void Resume(void) = 0;
	virtual std::weak_ptr<GameObject> AddObject(GameObject * go);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject * go) const;

	inline bool PopRequested (void) const { return popRequested; }
	inline bool QuitRequested (void) const { return quitRequested; }
};

#endif
