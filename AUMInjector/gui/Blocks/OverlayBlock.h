#pragma once
#include "GUIBlock.h"

class OverlayBlock : public GUIBlock
{
public:
	OverlayBlock(bool* trigger);

	void Update() override;

private:
	bool* buttonTrigger;
};

