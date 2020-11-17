#pragma once
#include <limits>
class MumblePlayer
{
public:
	// --- Ghost State --- 
	void EnterGhostState();

	void ExitGhostState();

	bool IsGhost();

	// --- Player Position --- 
	float GetMumblePos(int i);

	void SetPosX(float posX);

	void SetPosY(float posY);

	void SetFullVolume();

	void SetPos(int i, float pos);

	void TryLogPosition(bool force = false);

	// --- Events ---
	void StartMeeting();

	void EndMeeting();

	void StartCommunicationsSabotaged();

	void EndCommunicationsSabotaged();

	// Regardless of current state, it sets the user up for a new game
	void ResetState();

private:
	// --- Ghost State --- 
	// Is the player currently a ghost
	bool isGhost = false;
	
	void HandleGhostUnmute();

	// --- Player Position --- 
	void InvalidatePositionCache();
	// Where dead ghosts, using position audio, hang out
	const float graveyardOffset = 41134.0f;
	// Start old cache as an impossible limit, for first-frame printing
	float prevPosCache[2] = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
	// Position difference treshold for printing
	const float cachePosEpsilon = 0.001f;
	// Position
	float posCache[3] = { 0.0f, 0.0f, 0.0f };
	// Couters for tracking when to print the position
	unsigned int frameCounter = 0;
	// Const for how often to print the position
	const unsigned int framesToPrintPosition = 15;
	
	// -- Other States --
	bool isInMeeting = false;
	bool isSabotaged = false;
};
