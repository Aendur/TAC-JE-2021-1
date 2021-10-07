#include "InputManager.h"
#include "errors.h"
/*
bool mouseState[6];
int mouseUpdate[6];
std::unordered_map<int, bool> keyState;
std::unordered_map<int, int> keyUpdate;
bool quitRequested;
int updateCounter;
int mouseX;
int mouseY;
*/

InputManager::InputManager(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

InputManager::~InputManager(void) {
	//throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

InputManager & InputManager::GetInstance (void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void InputManager::Update(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::KeyPress(int key) {
	(void) key;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::KeyRelease(int key) {
	(void) key;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::IsKeyDown(int key) {
	(void) key;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::MousePress(int button) {
	(void) button;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::MouseRelease(int button) {
	(void) button;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::IsMouseDown(int button) {
	(void) button;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

int InputManager::GetMouseX(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

int InputManager::GetMouseY(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool InputManager::QuitRequested(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
