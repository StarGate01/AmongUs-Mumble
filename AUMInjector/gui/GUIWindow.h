#pragma once
#include <string>
#include <vector>
#include "GUIBlock.h"
#include "imgui.h"

class GUIWindow
{
public:
    explicit GUIWindow(std::string title, ImGuiWindowFlags wFlags);

    ~GUIWindow();

    void Update();

    void AddBlock(GUIBlock* editorBlock);

private:
    ImGuiWindowFlags windowFlags;
    std::string title_;
    std::vector<GUIBlock*> blocks_;
};

