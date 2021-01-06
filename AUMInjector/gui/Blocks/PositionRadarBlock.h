#pragma once

#ifdef DEV_TOOLS
#include "GUIBlock.h"

struct ImVec2;
struct ImVec4;
struct ImDrawList;

class PositionRadarBlock : public GUIBlock
{
public:
	PositionRadarBlock();

	void Update() override;
};

#endif

