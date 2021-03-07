#include "PlayerStateLobby.h"
#include "MumbleLink.h"
#include "PlayerStateMenu.h"
#include "PlayerStateAlive.h"
#include "PlayerStateGhost.h"
#include "PlayerStateMachine.h"

PlayerStateLobby::PlayerStateLobby()
{
	RegisterLink(PlayerStateMenu::stateID_, &PlayerStateLobby::EmptyLink);
	RegisterLink(PlayerStateAlive::stateID_, &PlayerStateLobby::EmptyLink);
	RegisterLink(PlayerStateGhost::stateID_, &PlayerStateLobby::EmptyLink);
	RegisterLink(PlayerStateLobby::stateID_, &PlayerStateLobby::EmptyLink);
}

void PlayerStateLobby::OnEnter()
{
	mumbleLink.Mute(false);
	GetParentStateMachine()->SetFullVolume();
}
