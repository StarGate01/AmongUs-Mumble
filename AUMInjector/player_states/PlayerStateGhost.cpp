#include "PlayerStateGhost.h"
#include "settings.h"
#include "MumbleLink.h"
#include "PlayerStateAlive.h"
#include "PlayerStateMeeting.h"
#include "PlayerStateMachine.h"

PlayerStateGhost::PlayerStateGhost()
{
    RegisterLink(PlayerStateAlive::stateID_, &PlayerStateGhost::EmptyLink);
    RegisterLink(PlayerStateMeeting::stateID_, &PlayerStateGhost::EmptyLink);
}

void PlayerStateGhost::OnEnter()
{
    // Mute based on ghost states
    switch (appSettings.ghostVoiceMode)
    {
    case Settings::GHOST_VOICE_MODE::PURGATORY:
    case Settings::GHOST_VOICE_MODE::HAUNT:
        mumbleLink.Mute(GetParentStateMachine()->IsCommunicationsSabotaged());
        break;
    case Settings::GHOST_VOICE_MODE::SPECTATE:
    default:
        mumbleLink.Mute(true);
    }
}

void PlayerStateGhost::SetPos(int i, float pos)
{
    // Override position based on ghost voice mode
    switch (appSettings.ghostVoiceMode)
    {
    case Settings::GHOST_VOICE_MODE::PURGATORY:
        GetParentStateMachine()->GetPosCache()[i] = graveyardOffset;
        break;
    case Settings::GHOST_VOICE_MODE::SPECTATE:
    case Settings::GHOST_VOICE_MODE::HAUNT:
    default:
        GetParentStateMachine()->GetPosCache()[i] = pos;
    };
}

void PlayerStateGhost::OnExit()
{
    // No longer a ghost, unmute them
    mumbleLink.Mute(false);
    // Make sure to log printing updates
    GetParentStateMachine()->InvalidatePositionCache();
}
