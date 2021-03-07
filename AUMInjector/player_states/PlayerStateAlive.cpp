#include "PlayerStateAlive.h"
#include "MumbleLink.h"
#include "PlayerStateLobby.h"
#include "PlayerStateMeeting.h"

PlayerStateAlive::PlayerStateAlive()
{
	RegisterLink(PlayerStateLobby::stateID_, &PlayerStateAlive::EmptyLink);
	RegisterLink(PlayerStateMeeting::stateID_, &PlayerStateAlive::EmptyLink);
}

void PlayerStateAlive::OnEnter()
{
	mumbleLink.Mute(false);
}
