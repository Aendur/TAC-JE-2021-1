#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//#include <string>
#include <unordered_map>

class InputManager {
private:
	bool mouseState[6];
	int mouseUpdate[6];
	
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	bool quitRequested;
	int updateCounter;
	int mouseX;
	int mouseY;

	InputManager(void);
	~InputManager(void);

public:
	static InputManager & GetInstance (void);

	void Update(void);

	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);

	int GetMouseX(void);
	int GetMouseY(void);

	bool QuitRequested(void);
};

#endif
