#include "State.h"
#include "GameObject.h"

State::~State(void) {
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject * go) {
	auto obj_ptr = std::shared_ptr<GameObject>(go);
	if (started) { obj_ptr->Start(); }
	objectArray.push_back(obj_ptr);
	return std::weak_ptr<GameObject>(obj_ptr);

}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject * go) const {
	for (auto & shared : objectArray) {
		if (go == shared.get()) {
			return std::weak_ptr<GameObject>(shared);
		}
	}
	return std::weak_ptr<GameObject>();
}

void State::StartArray(void) {
	for(size_t i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Start();
	}
}

void State::UpdateArray(float dt) {
	for(size_t i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Update(dt);
	}
}

void State::RenderArray(void) {
	for(size_t i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Render();
	}
}
