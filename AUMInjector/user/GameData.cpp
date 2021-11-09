#include "deobfuscate.h"
#include "GameData.h"


namespace AUM
{
	GameData* Game::_gameData = nullptr;

	void Game::SetGameData(GameData* gameData)
	{
		_gameData = gameData;
	}

	GameData* Game::GetGameData()
	{
		return _gameData;
	}

	PlayerControl* Game::GetPlayerControl(int netID)
	{
		auto controls = GetControls();

		auto iter = std::find_if(controls.begin(), controls.end(),
			[netID](PlayerControl* ctrl) -> bool
		{
			return ctrl->fields._.NetId == (uint32_t)netID;
		});

		// Does not exist 
		if (iter == controls.end())
			return nullptr;

		return *iter;
	}

#ifdef DEV_TOOLS

	Color Game::GetColor(PlayerControl* control)
	{
		// Get the player info 
		PlayerInfo* info = PlayerControl_GetData_Trampoline(control, NULL);
		// Color array not aligned correctly per il2cpp, is 4 byte aligned not 8 byte
		app::Color32* colorArr = ((((*Palette__TypeInfo)->static_fields)->*PlayerColors)->vector);
		// Convert to 8 bit * 4 structure to fix alignment
		uint8_t* color = (reinterpret_cast<uint8_t*>(colorArr) + info->fields.*ColorId * 4);

		return  { color[0], color[1], color[2], color[3] };
	}


	Color Game::GetColor(int netID) 
	{
		auto control = GetPlayerControl(netID);
		if (!control) return { 0, 0, 0, 0 };

		return GetColor(control);
	}

#endif

	Vec2 Game::GetPosition(PlayerControl* control)
	{
		Vector2 pos = PlayerControl_GetTruePosition_Trampoline(control, NULL);
		return { pos.x, pos.y };
	}

	Vec2 Game::GetPosition(int netID)
	{
		auto control = GetPlayerControl(netID);
		if (!control) return { 0.0f, 0.0f };

		return GetPosition(control);
	}

	std::vector<PlayerControl*> Game::GetControls()
	{
		// Get all current PlayerControls found in the game
		std::vector<PlayerControl*> result;
		ArrayList* controlList = reinterpret_cast<ArrayList*>((*PlayerControl__TypeInfo)->static_fields->AllPlayerControls);
		int count = ArrayList_get_Count(
			controlList,
			NULL);

		if (count == 0) return result;

		for (int i = 0; i < count; ++i)
		{
			result.push_back(reinterpret_cast<PlayerControl*>(ArrayList_get_Item(controlList, i, NULL)));
		}


		return result;
	}
}

