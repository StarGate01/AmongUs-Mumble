#include "AboutBlock.h"
#include "imgui.h"
#include "settings.h"
#include "version.h"

AboutBlock::AboutBlock() {}

void AboutBlock::Update()
{
    ImGui::Text("Compiled for game version %s", version_text);
    ImGui::Separator();
    ImGui::Text(CREDITS.c_str());   
}
