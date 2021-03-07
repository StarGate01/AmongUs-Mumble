#pragma once

#include "PlayerState.h"

class PlayerStateMeeting : public PlayerState<PlayerStateMeeting>
{
public:
	PlayerStateMeeting();

	void SetPos(int i, float pos) override;

	void OnEnter() override;

	void FromPlayerStateGhost(PlayerStateInterface* from);
};
