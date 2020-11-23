#include "MumblePlayer.h"
#include "Settings.h"
#include "MumbleLink.h"

MumblePlayer mumblePlayer;

// Will configure player to be a ghost, as per their config
void MumblePlayer::EnterGhostState()
{
    isGhost = true;
    // Spectator ghosts don't get to speak
    if (appSettings.ghostVoiceMode == Settings::GHOST_VOICE_MODE::SPECTATE)
        mumbleLink.Mute(true);
}

// Will configure player to be a player
void MumblePlayer::ExitGhostState()
{
    isGhost = false;
    // No longer a ghost, no need to have them muted
    mumbleLink.Mute(false);
    // Make sure log printing updates
    InvalidatePositionCache();
}

// On start meeting
void MumblePlayer::StartMeeting()
{
    isInMeeting = true;
    // ALL ghosts are muted durring meetings
    if (isGhost)
        mumbleLink.Mute(true);
    else
        mumbleLink.Mute(isSabotaged);
    // Make sure everyone can hear each other well
    SetFullVolume();
}

// On end meeting
void MumblePlayer::EndMeeting()
{
	isInMeeting = false;
	// Mute players and ghosts if comms sabotaged
	if (isSabotaged)
		mumbleLink.Mute(true);
	// Normal players get unmuted after meetings
	else if (!isGhost)
		mumbleLink.Mute(false);
	// Handle ghost unmuting
    else
		HandleGhostUnmute();
}

// On start communications sabotaged
void MumblePlayer::StartCommunicationsSabotaged()
{
    // Mute players AND ghosts
    isSabotaged = true;
    mumbleLink.Mute(true);
}

// On end communications sabotaged
void MumblePlayer::EndCommunicationsSabotaged()
{
    isSabotaged = false;
    // Handle player unmuting
    if(!isGhost)
        mumbleLink.Mute(false);
    // Handle ghost unmuting
    else
        HandleGhostUnmute();
}

// Regardless of current state, it sets the user up for a new game
void MumblePlayer::ResetState()
{
    // Reset everything to allow for new state updates
    frameCounter = 0;
    InvalidatePositionCache();
    isSabotaged = false;
    isInMeeting = false;
    if (isGhost)
        ExitGhostState();
    SetFullVolume();
    mumbleLink.Mute(false);
}

// Deals with unmuting a ghost based on the three voice settings
void MumblePlayer::HandleGhostUnmute()
{
    // Unmute based on ghost states
    switch (appSettings.ghostVoiceMode)
    {
    case Settings::GHOST_VOICE_MODE::PURGATORY:
    case Settings::GHOST_VOICE_MODE::HAUNT:
        mumbleLink.Mute(false);
        break;
    case Settings::GHOST_VOICE_MODE::SPECTATE:
    default:
        mumbleLink.Mute(true);
    }
}

// Reset cache (will force a log print)
void MumblePlayer::InvalidatePositionCache()
{
    prevPosCache[0] = std::numeric_limits<float>::lowest();
    prevPosCache[1] = std::numeric_limits<float>::lowest();
}

// Returns if the player is a ghost or not
bool MumblePlayer::IsGhost() { return isGhost; }

bool MumblePlayer::IsSabotaged() { return isSabotaged; }

bool MumblePlayer::IsInMeeting() { return isInMeeting; }

bool MumblePlayer::IsInGame() { return isInGame; }

bool MumblePlayer::IsInLobby() { return isInLobby; }

bool MumblePlayer::IsHost() { return isHost; }

void MumblePlayer::SetHost(bool host) { isHost = host; }

// Returns the mumble-ready position of the player
float MumblePlayer::GetMumblePos(int i) { return posCache[appSettings.audioCoordinateMap[i]]; }

// Set the x position cache, class may choose to override this value
void MumblePlayer::SetPosX(float posX) { SetPos(0, posX); }

// Set the y position cache, class may choose to override this value
void MumblePlayer::SetPosY(float posY) { SetPos(1, posY); }

int MumblePlayer::GetNetID() { return netID; }

void MumblePlayer::SetNetID(int id) { netID = id; }

// In mumble (0.0f, 0.0f) lets users hear each other better
void MumblePlayer::SetFullVolume()
{
    posCache[0] = 0.0f;
    posCache[1] = 0.0f;
}

// Sets the position cache, class may choose to override this value
void MumblePlayer::SetPos(int i, float pos)
{
	if (isInMeeting) // Everyone in a meeting should be at 0,0
		posCache[i] = 0.0f;
	else if (!IsGhost())
		posCache[i] = pos;
    else
    {
        // Override position based on ghost voice mode
        switch (appSettings.ghostVoiceMode)
        {
        case Settings::GHOST_VOICE_MODE::PURGATORY:
            posCache[i] = graveyardOffset;
            break;
        case Settings::GHOST_VOICE_MODE::SPECTATE:
        case Settings::GHOST_VOICE_MODE::HAUNT:
        default:
            posCache[i] = pos;
        }
    }
}

// Will log the position, if needed
void MumblePlayer::TryLogPosition(bool force)
{
	// Only print the player position every so many frames, and if it has changed
	if (force || (++frameCounter > framesToPrintPosition && (
			std::abs(prevPosCache[0] - posCache[0]) > cachePosEpsilon ||
			std::abs(prevPosCache[1] - posCache[1]) > cachePosEpsilon
			)
        ))
	{
        frameCounter = 0;
        // Store the old position
        prevPosCache[0] = posCache[0];
        prevPosCache[1] = posCache[1];
        // Log the current player position to let the player know it is working
        if (mumbleLink.linkedMem != nullptr)
        {
            // Change log message based on if player is a ghost or not
            if (isGhost)
                logger.LogVariadic(LOG_CODE::MSG, true, "Linked - Ghost Position: (%.3f, %.3f)      ",
                    posCache[0], posCache[1]);
            else
                logger.LogVariadic(LOG_CODE::MSG, true, "Linked - Position: (%.3f, %.3f)      ",
                    posCache[0], posCache[1]);
        }
    }
}

// Player entered a game
void MumblePlayer::EnterGame()
{
    isInGame = true;
    isInLobby = false;
}

// Player entered a lobby
void MumblePlayer::EnterLobby()
{
    isInLobby = true;
    isInGame = false;
}

// Player exited a game
void MumblePlayer::ExitGame()
{
    isInGame = false;
    isInLobby = false;
}

