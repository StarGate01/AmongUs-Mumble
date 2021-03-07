#pragma once

#include "PlayerState.h"

class PlayerStateAlive : public PlayerState<PlayerStateAlive>
{
public:
	PlayerStateAlive();

	void OnEnter() override;
};
