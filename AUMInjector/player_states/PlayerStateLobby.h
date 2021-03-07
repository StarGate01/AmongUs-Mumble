#pragma once

#include "PlayerState.h"

class PlayerStateLobby : public PlayerState<PlayerStateLobby>
{
public:
	PlayerStateLobby();

	void OnEnter() override;
};
