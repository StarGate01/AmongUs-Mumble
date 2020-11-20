#pragma once
#include <string>
#include <vector>
#include "GUIBlock.h"


class GUIWindow
{
public:
    explicit GUIWindow(std::string title);

    ~GUIWindow();

    void Update();

    void AddBlock(GUIBlock* editorBlock);

private:
    std::string title_;
    std::vector<GUIBlock*> blocks_;
    bool showWindow_;
};

