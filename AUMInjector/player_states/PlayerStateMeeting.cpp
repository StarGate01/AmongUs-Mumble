#include "PlayerStateMeeting.h"
#include "MumbleLink.h"
#include "PlayerStates.h"

PlayerStateMeeting::PlayerStateMeeting()
{
	RegisterLink(PlayerStateAlive::stateID_, &PlayerStateMeeting::EmptyLink);
	RegisterLink(PlayerStateGhost::stateID_, &PlayerStateMeeting::FromPlayerStateGhost);
}

void PlayerStateMeeting::SetPos(int i, float pos)
{
	GetParentStateMachine()->GetPosCache()[i] = 0;
}

void PlayerStateMeeting::OnEnter()
{
	GetParentStateMachine()->SetFullVolume();
}

void PlayerStateMeeting::FromPlayerStateGhost(PlayerStateInterface* from)
{
	mumbleLink.Mute(true);
}
