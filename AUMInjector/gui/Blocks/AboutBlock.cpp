#include "AboutBlock.h"
#include "imgui.h"
#include "settings.h"

AboutBlock::AboutBlock() {}

void AboutBlock::Update()
{
    ImGui::Text(CREDITS.c_str());
}
