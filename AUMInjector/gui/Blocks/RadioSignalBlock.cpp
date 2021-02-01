#include "RadioSignalBlock.h"
#include "imgui.h"
#include "MumblePlayer.h"

RadioSignalBlock::RadioSignalBlock() {}

void RadioSignalBlock::Update()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 size(ImGui::GetWindowSize());
    // Offset for the borders of the window because size of canvas
    // is less than size of window
    size.x -= 20.0f;
    size.y -= 20.0f;
    // This makes the canvas
    ImGui::InvisibleButton("canvas", size);
    // Get canvas boundaries
    ImVec2 p0 = ImGui::GetItemRectMin();
    ImVec2 p1 = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->PushClipRect(p0, p1);
    if(mumblePlayer.IsRadioInUse()) {
        // Draw a green square when radio is not in use
        draw_list->AddRectFilled(p0, p1, IM_COL32(0, 255, 0, 255));
    }
    else {
        // Draw a red square when radio is not in use
        draw_list->AddRectFilled(p0, p1, IM_COL32(255, 0, 0, 255));
    }
    draw_list->PopClipRect();
}
