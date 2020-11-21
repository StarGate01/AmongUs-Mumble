#include "OverlayBlock.h"
#include "imgui.h"
#include "MumblePlayer.h"

OverlayBlock::OverlayBlock(bool* trigger):
    buttonTrigger(trigger)
{}

void OverlayBlock::Update()
{
    if (ImGui::Button("Proximity Configuration", ImVec2(0.0f, 30.0f)))
        *buttonTrigger = !(*buttonTrigger);
}
