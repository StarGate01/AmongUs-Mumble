#pragma once
#include <deobfuscate.h>

// Custom definitions for our game state and other data
namespace AUM
{
	struct Vec2
	{
		float x, y;
	};

	// 0 to 255
	struct Color
	{
		uint8_t r, g, b, a;
	};

	class Game
	{
	public:
		static void SetGameData(GameData* gameData);
		static GameData* GetGameData();

		// Get most recent player control from net ID
		static PlayerControl* GetPlayerControl(int netID);
		// Get current list of player controls in game
		static std::vector<PlayerControl*> GetControls();

#ifdef DEV_TOOLS

		// Get color from existing player control
		static Color GetColor(PlayerControl* control);
		// Get updated player control from Net ID and then grab color
		static Color GetColor(int netID);

#endif

		// Get position from existing player control
		static Vec2 GetPosition(PlayerControl* control);
		// Get updated player control from Net ID and then grab position
		static Vec2 GetPosition(int netID);

	private:
		static GameData* _gameData;
	};
}

