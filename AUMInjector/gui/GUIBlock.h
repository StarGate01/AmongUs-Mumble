#pragma once
class GUIBlock
{
public:
    GUIBlock() = default;

    virtual ~GUIBlock() = default;

    virtual void Update() = 0;
};

