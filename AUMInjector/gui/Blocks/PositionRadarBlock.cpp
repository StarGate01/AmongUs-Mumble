#ifdef DEV_TOOLS

// Output position / color data to ImGui
#include "PositionRadarBlock.h"
#include "GameData.h"
#include "imgui.h"
#include "MumblePlayer.h"

constexpr float size = 10.0f;

ImVec4& NormalizeColor(ImVec4& color)
{
    color.x /= 255.0f;
    color.y /= 255.0f;
    color.z /= 255.0f;
    color.w /= 255.0f;
    return color;
}

PositionRadarBlock::PositionRadarBlock() {}

#define V2 ImVec2
void FX(ImDrawList* d, V2 a, V2 b, V2 sz, AUM::Vec2 playerPos)
{
    // for (int n = 0; n < (1.0f + sinf(t * 5.7f)) * 40.0f; n++)
    //     d->AddCircle(V2(a.x + sz.x * 0.5f, a.y + sz.y * 0.5f), sz.y * (0.01f + n * 0.03f),
    //         IM_COL32(255, 140 - n * 4, n * 3, 255));

    const ImVec2 centerCanvas(a.x + sz.x * 0.5f, a.y + sz.y * 0.5f);
    int playerNetID = mumblePlayer.GetNetID();

    auto playerColor = AUM::Game::GetColor(playerNetID);
    ImVec4 playerDrawColor = ImVec4(playerColor.r, playerColor.g, playerColor.b, playerColor.a);

    d->AddCircle(centerCanvas, size / 3, 
        (ImColor)NormalizeColor(playerDrawColor), 
        0, size / 2);

    auto controls = AUM::Game::GetControls();

    // For each player control, get position and color
	for (const auto& control : controls)
	{
        int netID = control->fields._.NetId;
		if (netID == playerNetID) continue;

		// Center the radar
		auto pos = AUM::Game::GetPosition(control);
		auto diffX = (pos.x - playerPos.x) * 5.0f;
		auto diffY = (pos.y - playerPos.y) * 5.0f;

		ImVec2 canvasPosition(centerCanvas.x + diffX, centerCanvas.y - diffY);

		auto color = AUM::Game::GetColor(control);
		ImVec4 drawColor = ImVec4(color.r, color.g, color.b, color.a);

		d->AddCircle(canvasPosition, size / 2, (ImColor)NormalizeColor(drawColor), 0, size / 4);
	}
}

void PositionRadarBlock::Update()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 size(ImGui::GetWindowSize());
    // Offset for the borders of the window because size of canvas
	// is less than size of window
    size.x -= 20.0f;
    size.y -= 40.0f;
    // This makes the canvas
    ImGui::InvisibleButton("canvas", size);
    // Get canvas boundaries
    ImVec2 p0 = ImGui::GetItemRectMin();
    ImVec2 p1 = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->PushClipRect(p0, p1);

    ImVec4 mouse_data;
    mouse_data.x = (io.MousePos.x - p0.x) / size.x;
    mouse_data.y = (io.MousePos.y - p0.y) / size.y;
    mouse_data.z = io.MouseDownDuration[0];
    mouse_data.w = io.MouseDownDuration[1];

    FX(draw_list, p0, p1, size, { mumblePlayer.posCache[0], mumblePlayer.posCache[1] });
    draw_list->PopClipRect();
}

#endif