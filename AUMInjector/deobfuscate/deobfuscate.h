// This file contains deobfuscation mappings for different versions of the game

#pragma once
#include "version.h"

using namespace app;

// Deobfuscate game bindings, depending on version
#if GAME_VERSION == GAME_VERSION_2020_9_22s
	#include "2020_9_22s.h"
#elif GAME_VERSION == GAME_VERSION_2020_10_22s
	#include "2020_10_22s.h"
#elif GAME_VERSION == GAME_VERSION_2020_11_4s
	#include "2020_11_4s.h"
#elif GAME_VERSION == GAME_VERSION_2020_11_17s
	#include "2020_11_17s.h"
#elif GAME_VERSION == GAME_VERSION_2020_11_17s_1
	#include "2020_11_17s_1.h"
#elif GAME_VERSION == GAME_VERSION_2020_12_3s
	#include "2020_12_3s.h"
#elif GAME_VERSION == GAME_VERSION_2020_12_5s
	#include "2020_12_5s.h"
#elif GAME_VERSION == GAME_VERSION_2020_12_9s
	#include "2020_12_9s.h"
#elif GAME_VERSION == GAME_VERSION_2021_3_5s
	#include "2021_3_5s.h"
#elif GAME_VERSION == GAME_VERSION_2021_3_31_3s
	#include "2021_3_31_3s.h"
#elif GAME_VERSION == GAME_VERSION_2021_4_12s
	#include "2021_4_12s.h"
#elif GAME_VERSION == GAME_VERSION_2021_4_14s
	#include "2021_4_14s.h"
#elif GAME_VERSION == GAME_VERSION_2021_5_10s
	#include "unobfuscated.h"
#elif GAME_VERSION == GAME_VERSION_2021_5_25s
	#include "unobfuscated.h"
#elif GAME_VERSION == GAME_VERSION_2021_6_15s
	#include "unobfuscated.h"
#else
	#error Unknown game version!
#endif