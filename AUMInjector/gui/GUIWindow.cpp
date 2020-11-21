#include "GUIWindow.h"
#include "imgui.h"

GUIWindow::GUIWindow(std::string title, ImGuiWindowFlags wFlags) : 
	title_(std::move(title)), 
	windowFlags(wFlags)
{
}

GUIWindow::~GUIWindow()
{
    for (auto block : blocks_) delete block;
}

void GUIWindow::Update()
{
	ImGui::Begin(title_.c_str(), nullptr, windowFlags);
	for (auto block : blocks_)
		block->Update();
	ImGui::End();
}

void GUIWindow::AddBlock(GUIBlock* editorBlock)
{
    blocks_.emplace_back(editorBlock);
}

