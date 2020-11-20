#include "SettingsBlock.h"
#include "imgui.h"
#include "Settings.h"
#include <string.h>

const char* booleanOptions[] = { "False", "True" };

SettingsBlock::SettingsBlock()
{

}

void BoolComboHelper(bool &comboBoolean, const char* label)
{
    if (ImGui::BeginCombo((std::string("##") + label).c_str(), booleanOptions[comboBoolean])) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(booleanOptions); n++)
        {
            if (ImGui::Selectable(booleanOptions[n], booleanOptions[comboBoolean] == booleanOptions[n]))
                comboBoolean = n;
        }
        ImGui::EndCombo();
    }
}

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        std::string* str = (std::string*)data->UserData;
        IM_ASSERT(data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
    }
    return 0;
}

namespace ImGui
{
    bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = ImGuiInputTextFlags_None)
    {
        flags |= ImGuiInputTextFlags_CallbackResize;
        return InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, (void*)str);
    }
}


void SettingsBlock::Update()
{
	ImGui::Text("Config Constants:");
    ImGui::Text("These settings will only update after a restart.");
    ImGui::Text("Mumble EXE Path: ");
    ImGui::InputText("##mumbleEXE", &appSettings.mumbleExe);

    ImGui::Text("Log File Path: ");
    ImGui::InputText("##logFileName", &appSettings.logFileName);

    ImGui::Separator();
	ImGui::Text("Config Settings:");
    
    ImGui::Text("Disable Console Log:");
    BoolComboHelper(appSettings.disableLogConsole, "logToConsole");
    
    ImGui::Text("Disable File Log:");
    ImGui::TextWrapped("It's recommended that you do not disable the following as, if you ever need help, this file is needed.");
    BoolComboHelper(appSettings.disableLogFile, "logToFile");

    // Parse the current settings and write them to the config, if requested
    if (ImGui::Button("Save Config"))
    {
        // TODO: Write config here
    }
}
