#include "MumblePlayer.h"
#include "Settings.h"
#include "MumbleLink.h"

void MumblePlayer::EnterGhostState()
{
    // Spectator ghosts don't get to speak
    if (appSettings.ghostVoiceMode == Settings::GHOST_VOICE_MODE::SPECTATE)
        mumbleLink.Mute(true);
    isGhost = true;
}

void MumblePlayer::ExitGhostState()
{
    // No longer a ghost, no need to have them muted
    mumbleLink.Mute(false);
    isGhost = false;
    SetFullVolume();
}

void MumblePlayer::StartMeeting()
{
    isInMeeting = true;
    // ALL ghosts are muted durring meetings
    if (isGhost)
        mumbleLink.Mute(true);
    else
        mumbleLink.Mute(isSabotaged);
    SetFullVolume();
}

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

void MumblePlayer::StartCommunicationsSabotaged()
{
    isSabotaged = true;
    mumbleLink.Mute(true);
}

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

void MumblePlayer::ResetState()
{
    frameCounter = 0;
    InvalidatePositionCache();
    isSabotaged = false;
    isInMeeting = false;
    if (isGhost)
        ExitGhostState();
    SetFullVolume();
    mumbleLink.Mute(false);
}

void MumblePlayer::HandleGhostUnmute()
{
    // Unmute based on ghost states
    switch (appSettings.ghostVoiceMode)
    {
    case Settings::GHOST_VOICE_MODE::PURGATORY:
    case Settings::GHOST_VOICE_MODE::HAUNT:
        mumbleLink.Mute(false);
    case Settings::GHOST_VOICE_MODE::SPECTATE:
    default:
        mumbleLink.Mute(true);
    }
}

void MumblePlayer::InvalidatePositionCache()
{
    prevPosCache[0] = std::numeric_limits<float>::lowest();
    prevPosCache[1] = std::numeric_limits<float>::lowest();
}

bool MumblePlayer::IsGhost() { return isGhost; }

float MumblePlayer::GetMumblePos(int i) { return posCache[appSettings.audioCoordinateMap[i]]; }

void MumblePlayer::SetPosX(float posX) { SetPos(0, posX); }

void MumblePlayer::SetPosY(float posY) { SetPos(1, posY); }

void MumblePlayer::SetFullVolume()
{
    posCache[0] = 0.0f;
    posCache[1] = 0.0f;
}

void MumblePlayer::SetPos(int i, float pos)
{
	if (!IsGhost())
		posCache[i] = pos;
	else if (isInMeeting)
		posCache[i] = 0.0f;
    else
    {
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
            if (isGhost)
                logger.LogVariadic(LOG_CODE::MSG, true, "Linked - Ghost Position: (%.3f, %.3f)      ",
                    posCache[0], posCache[1]);
            else
                logger.LogVariadic(LOG_CODE::MSG, true, "Linked - Position: (%.3f, %.3f)      ",
                    posCache[0], posCache[1]);
        }
    }
}

