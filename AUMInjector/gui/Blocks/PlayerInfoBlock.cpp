#include "PlayerInfoBlock.h"
#include "imgui.h"
#include "../player_states/PlayerStateMachine.h"
#include "../../player_states/PlayerStateLobby.h"
#include "../../player_states/PlayerStateAlive.h"
#include "../../player_states/PlayerStateGhost.h"
#include "../../player_states/PlayerStateMeeting.h"

PlayerInfoBlock::PlayerInfoBlock() {}

void PlayerInfoBlock::Update()
{
	ImGui::Text("Player Position: (%.3f, %.3f)", playerStateMachine.GetPosCache()[0], playerStateMachine.GetPosCache()[1]);
	ImGui::Text("Player is in a lobby: %s", playerStateMachine.GetCurrentStateID() == PlayerStateLobby::stateID_ ? "True" : "False");
	ImGui::Text("Player is alive: %s", playerStateMachine.GetCurrentStateID() == PlayerStateAlive::stateID_ ? "True" : "False");
	ImGui::Text("Player is a ghost: %s",  playerStateMachine.GetCurrentStateID() == PlayerStateGhost::stateID_ ? "True" : "False");
	ImGui::Text("Player is in a meeting: %s", playerStateMachine.GetCurrentStateID() == PlayerStateMeeting::stateID_  ? "True" : "False");
	ImGui::Text("Communications is sabotaged: %s", playerStateMachine.IsCommunicationsSabotaged() ? "True" : "False");
}
