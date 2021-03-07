#pragma once

#include "PlayerState.h"

class PlayerStateMenu : public PlayerState<PlayerStateMenu>
{
public:
	PlayerStateMenu();

	void OnEnter() override;
};
