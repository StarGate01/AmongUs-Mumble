#pragma once
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

	bool IsSabotaged();

	bool IsInMeeting();

	bool IsInGame();

	bool IsInLobby();

	bool IsHost();

	void SetHost(bool host);

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

	// Player entered a game
	void EnterGame();

	// Player exited a game
	void ExitGame();

	// Player entered a lobby
	void EnterLobby();

	// Returns the player's net ID
	int GetNetID();

	// Sets the player's net ID
	void SetNetID(int id);

	// Sets whether player is imposter
	void SetImposter(bool imposter);
	
	// Clears player from being imposter
	void ClearImposter();

	// Returns if player is imposter
	bool IsImposter() const;

	// Returns if player is using radio
	bool IsUsingRadio() const;

	// Sets if the player is using radio
	void SetUsingRadio(bool usingRadio);

private:
	// --- Ghost State --- 
	// Is the player currently a ghost
	bool isGhost = false;
	
	// Deals with un-muting a ghost based on the three voice settings
	void HandleGhostUnmute();

	// --- Player Position --- 
	// Reset cache (will force a log print)
	void InvalidatePositionCache();

	// Where dead ghosts, using position audio, hang out
	const float graveyardOffset = 41134.0f;

	// Start old cache as an impossible limit, for first-frame printing
	float prevPosCache[2] = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };

	// Position difference threshold for printing
	const float cachePosEpsilon = 0.001f;

	// Position
	float posCache[3] = { 0.0f, 0.0f, 0.0f };

	// Counters for tracking when to print the position
	unsigned int frameCounter = 0;

	// Const for how often to print the position
	const unsigned int framesToPrintPosition = 15;
	
	// -- Other State Info --
	bool isInMeeting = false;
	bool isInLobby = false;
	bool isSabotaged = false;
	bool isInGame = false;

	// Cached player network id
	int netID = 0;

	bool isHost = false;

	// Imposter flag
	bool isImposter = false;
	// Using Radio flag
	bool isUsingRadio = false;
	// When you're using radio, teleport here
	const float radioOffset = 19999.0f;

	// Reads private information to display it to the user
	friend class PlayerInfoBlock;
};

extern MumblePlayer mumblePlayer;
