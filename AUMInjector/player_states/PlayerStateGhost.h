#pragma once

#include "PlayerState.h"

class PlayerStateGhost : public PlayerState<PlayerStateGhost>
{
public:
	PlayerStateGhost();

	void OnEnter() override;

	void SetPos(int i, float pos) override;

	void OnExit() override;

	// Where dead ghosts, using position audio, hang out
	const float graveyardOffset = 41134.0f;
};
