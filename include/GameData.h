#ifndef GAMEDATA_H
#define GAMEDATA_H

class GameData {
public:
	enum VictoryState {
		UNDEFINED,
		VICTORY,
		DEFEAT,
	};

	inline static VictoryState playerVictory = UNDEFINED;
};

#endif
