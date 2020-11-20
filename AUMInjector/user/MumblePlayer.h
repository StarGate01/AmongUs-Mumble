#pragma once
#include <limits>
class MumblePlayer
{
public:
	// --- Ghost State --- 
	// Will configure player to be a ghost, as per their config
	void EnterGhostState();

	// Will configure player to be a player
	void ExitGhostState();

	// Returns if the player is a ghost or not
	bool IsGhost();

	// --- Player Position --- 
	// Returns the mumble-ready position of the player
	float GetMumblePos(int i);

	// Set the x position cache, class may choose to override this value
	void SetPosX(float posX);

	// Set the y position cache, class may choose to override this value
	void SetPosY(float posY);

	// In mumble (0.0f, 0.0f) lets users hear each other better
	void SetFullVolume();

	// Sets the position cache, class may choose to override this value
	void SetPos(int i, float pos);

	// Will log the position, if needed
	void TryLogPosition(bool force = false);

	// --- Other Events ---
	// On start meeting
	void StartMeeting();

	// On end meeting
	void EndMeeting();

	// On start communications sabotaged
	void StartCommunicationsSabotaged();

	// On end communications sabotaged
	void EndCommunicationsSabotaged();

	// Regardless of current state, it sets the user up for a new game
	void ResetState();

	// Cached player network id
	int netID = 0;

private:
	// --- Ghost State --- 
	// Is the player currently a ghost
	bool isGhost = false;
	
	// Deals with unmuting a ghost based on the three voice settings
	void HandleGhostUnmute();

	// --- Player Position --- 
	// Reset cache (will force a log print)
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
	
	// -- Other State Info --
	bool isInMeeting = false;
	bool isSabotaged = false;

	// Reads private information to display it to the user
	friend class PlayerInfoBlock;
};

extern MumblePlayer mumblePlayer;
