#include "SettingsBlock.h"
#include "imgui.h"
#include "Settings.h"
#include <string.h>
#include "LoggingSystem.h"
#include "MumblePlayer.h"

// Based on enums (wish we hand non-standard GCC extensions here)
const char* booleanOptions[] = { "False", "True" };
const char* voiceText[] = { "Purgatory", "Spectate", "Haunt" };
const char* verbosityText[] = { "Error", "Warning", "Info", "Message", "Debug" };


SettingsBlock::SettingsBlock() { }

// Creates a combo for booleans
void BoolComboHelper(bool &comboBoolean, const char* label, bool shouldRecalculateAudio = false)
{
    if (ImGui::BeginCombo((std::string("##") + label).c_str(), booleanOptions[comboBoolean]))
    {
        for (int n = 0; n < IM_ARRAYSIZE(booleanOptions); n++)
        {
            if (ImGui::Selectable(booleanOptions[n], booleanOptions[comboBoolean] == booleanOptions[n]))
            {
                comboBoolean = n;

                // In the case that audio settings are being changed
                if(shouldRecalculateAudio)
                {
					appSettings.RecalculateAudioMap();
					appSettings.mustBroadcast = true;
				}
			}
		}
        ImGui::EndCombo();
    }
}

// Callback to append to a string
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

// Input text that writes to a string, so no overflows
namespace ImGui
{
    bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = ImGuiInputTextFlags_None)
    {
        flags |= ImGuiInputTextFlags_CallbackResize;
        return InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, (void*)str);
    }
}

// Makes a combo from a given enum type
template <typename ENUM_TYPE>
void EnumComboHelper(const char* label, const char* str, const char** arr, ENUM_TYPE& value)
{
    if (ImGui::BeginCombo(label, str))
    {
        for (int n = 0; n < (int)ENUM_TYPE::COUNT; n++)
            if (ImGui::Selectable(arr[n], (int)value == n))
            {
                value = (ENUM_TYPE)n;
                appSettings.mustBroadcast = true;
            }
        ImGui::EndCombo();
    }
}

void SettingsBlock::Update()
{
    // Config settings that can be changed each round
    ImGui::Text("[ Game Settings ]");

    // If the user is in a game, don't let them change the settings and only display them
    if (mumblePlayer.IsInGame() || (mumblePlayer.IsInLobby() && !mumblePlayer.IsHost()))
    {
        // Print current settings only, as they can't be changed.
        if (mumblePlayer.IsInGame())
        {
            ImGui::Text("You cannot change game settings while in a round.");
        }
        else
        {
            ImGui::Text("You cannot change game settings.");
            ImGui::Text("Only the lobby host can do that.");
        }
        ImGui::Text("Ghost voice mode: %s", voiceText[(int)appSettings.ghostVoiceMode]);
        ImGui::Text("Directional Audio: %s", appSettings.directionalAudio ? "True" : "False");
    }
    else
    {
        ImGui::Text("These settings will be applied to next round.");

        // Ghost voice mode verbosity setting
        if (ImGui::TreeNode("Ghost Voice Mode:"))
        {
            ImGui::Text("Purgatory: Ghosts can talk to each other regardless of their position, but cannot listen to remaining players.");
            ImGui::Text("Spectate : Ghosts are muted, but can listen to remaining players if they are close enough.");
            ImGui::Text("Haunt : Ghosts can talkand listen to remaining players if they are close enough.");
            ImGui::TreePop();
        }
        EnumComboHelper<Settings::GHOST_VOICE_MODE>(
            "##comboGhostVoiceMode",
            voiceText[(int)appSettings.ghostVoiceMode],
            voiceText,
            appSettings.ghostVoiceMode
            );

        // Proximity audio mode
        if (ImGui::TreeNode("Directional Audio:"))
        {
            ImGui::TextWrapped("This does NOT enable/diable proximity.");
            ImGui::Text("It changes how positional audio sounds.");
            ImGui::TreePop();
        }
        BoolComboHelper(appSettings.directionalAudio, "directionalAudio", true);
    }

    ImGui::Separator();

    // Config settings that only change after a restart
    ImGui::Text("[ General Settings ]");
    ImGui::Text("These settings will be applied after a restart.");

    // Mumble EXE Path
    if (ImGui::TreeNode("Mumble Executable Path:"))
    {
        ImGui::Text("Specifies the path of the mumble EXE file.");
        ImGui::TreePop();
    }
    ImGui::InputText("##mumbleEXE", &appSettings.mumbleExe);

    // Disable button overlay
    if (ImGui::TreeNode("Disable Overlay Button:"))
    {
        ImGui::Text("Disables the configuration button overlay.");
        ImGui::TreePop();
    }
    BoolComboHelper(appSettings.disableOverlay, "overlay");

    // Log File
    if (ImGui::TreeNode("Logfile path:"))
    {
        ImGui::Text("Specifies the name of the log file.");
        ImGui::TreePop();
    }
    ImGui::InputText("##logFileName", &appSettings.logFileName);

    // Disable console log setting
    if (ImGui::TreeNode("Disable Console Log:"))
    {
        ImGui::Text("Disables and does not create the console window.");
        ImGui::TreePop();
    }
    BoolComboHelper(appSettings.disableLogConsole, "logToConsole");

    // Disable log file setting
    if (ImGui::TreeNode("Disable File Log:"))
    {
        ImGui::Text("Disables and does not create the log file.");
        ImGui::Text("It is recommended you do not disable this as it will help if you have and problems.");
        ImGui::TreePop();
    }
    BoolComboHelper(appSettings.disableLogFile, "logToFile");

    // Log file verbosity setting
    if (ImGui::TreeNode("Log Verbosity:"))
    {
        ImGui::Text("Sets how verbose the log file will be.");
        ImGui::Text("Debug is the highest.");
        ImGui::Text("Error is the lowest.");
        ImGui::TreePop();
    }
    EnumComboHelper<LOG_CODE>(
        "##comboVerbosity",
        verbosityText[(int)logger.verbosity],
        verbosityText,
        appSettings.logVerbosity
        );
    logger.verbosity = appSettings.logVerbosity; // Sync verbosity levels

    ImGui::Separator();

    // Write the settings to the config, if requested
    if (ImGui::Button("Save to config file"))
        appSettings.Save();
}
