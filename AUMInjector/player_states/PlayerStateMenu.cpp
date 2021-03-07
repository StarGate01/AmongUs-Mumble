#include "PlayerStateMenu.h"
#include "PlayerStateMachine.h"
#include "MumbleLink.h"
#include "PlayerStateAlive.h"
#include "PlayerStateLobby.h"
#include "PlayerStateMeeting.h"
#include "PlayerStateGhost.h"

PlayerStateMenu::PlayerStateMenu()
{
	RegisterLink(PlayerStateAlive::stateID_, &PlayerStateMenu::EmptyLink);
	RegisterLink(PlayerStateLobby::stateID_, &PlayerStateMenu::EmptyLink);
	RegisterLink(PlayerStateMeeting::stateID_, &PlayerStateMenu::EmptyLink);
	RegisterLink(PlayerStateGhost::stateID_, &PlayerStateMenu::EmptyLink);
	RegisterLink(PlayerStateMenu::stateID_, &PlayerStateMenu::EmptyLink);
}

void PlayerStateMenu::OnEnter()
{
	GetParentStateMachine()->SetFullVolume();
	mumbleLink.Mute(false);
}
