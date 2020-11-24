#define GAME_VERSION_2020_9_22s 20209220
#define GAME_VERSION_2020_10_22s 202010220
#define GAME_VERSION_2020_11_4s 202011040
#define GAME_VERSION_2020_11_17s 202011170
#ifndef GAME_VERSION
	#define GAME_VERSION GAME_VERSION_2020_11_17s
#endif

#if GAME_VERSION == GAME_VERSION_2020_9_22s
	#define version_text "2020.9.22s"
#elif GAME_VERSION == GAME_VERSION_2020_10_22s
	#define version_text "2020.10.22s"
#elif GAME_VERSION == GAME_VERSION_2020_11_4s
	#define version_text "2020.11.4s"
#elif GAME_VERSION == GAME_VERSION_2020_11_17s
	#define version_text "2020.11.17s"
#else
	#error Unknown game version!
#endif

#pragma message("Compiling for game version " version_text)