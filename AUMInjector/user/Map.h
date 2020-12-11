#pragma once

#include <string>
#include <vector>
#include "il2cpp-appdata.h"


using namespace app;


// Provides access to the collision map
class Map
{

	public:
		Map();

		// Rebuilds the cached state from the game state
		void Rebuild();

	private:
		// Finds all colliders and converts them
        template<typename T> void AddAddColliders(std::string netname);

		// What collider names shall not be included
		std::vector<std::string> nameBlacklist;

		// String conversion helper
		std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;

};

extern Map map;