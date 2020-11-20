#include "GUIWindow.h"
#include "imgui.h"

GUIWindow::GUIWindow(std::string title): title_(std::move(title)), showWindow_(true)
{
}

GUIWindow::~GUIWindow()
{
    for (auto block : blocks_)
        delete block;
}

void GUIWindow::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	if (showWindow_)
	{
		ImGui::Begin(title_.c_str(), &showWindow_, window_flags);
		for (auto block : blocks_)
			block->Update();
		ImGui::End();
	}
}

void GUIWindow::AddBlock(GUIBlock* editorBlock)
{
    blocks_.emplace_back(editorBlock);
}

