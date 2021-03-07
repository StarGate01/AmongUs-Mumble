#include "PlayerState.h"
#include "PlayerStateMachine.h"

PlayerStateInterface::PlayerStateInterface(unsigned ID) { stateID_ = ID; }

unsigned GetNextId() noexcept
{
	static unsigned nextID = 0;
	return ++nextID;
}

inline void PlayerStateInterface::SetPos(int i, float pos)
{
	GetParentStateMachine()->GetPosCache()[i] = pos;
}
