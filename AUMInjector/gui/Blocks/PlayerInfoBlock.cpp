#include "PlayerInfoBlock.h"
#include "imgui.h"
#include "MumblePlayer.h"

PlayerInfoBlock::PlayerInfoBlock() {}

void PlayerInfoBlock::Update()
{
	ImGui::Text("Player Position: (%.3f, %.3f)", mumblePlayer.posCache[0], mumblePlayer.posCache[1]);
	ImGui::Text("Player is a ghost: %s", mumblePlayer.isGhost ? "True" : "False");
	ImGui::Text("Player is in a meeting: %s", mumblePlayer.isInMeeting ? "True" : "False");
	ImGui::Text("Communications is sabotaged: %s", mumblePlayer.isSabotaged ? "True" : "False");
}
