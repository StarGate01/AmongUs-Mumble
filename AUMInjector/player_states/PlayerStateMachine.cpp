#include "PlayerStateMachine.h"
#include "settings.h"
#include "PlayerStateMenu.h"
#include "PlayerStateGhost.h"
#include "MumbleLink.h"

extern PlayerStateMachine playerStateMachine(new PlayerStateMenu());

PlayerStateMachine::PlayerStateMachine(PlayerStateInterface* startGameState) : currentState(startGameState)
{
    startGameState->SetParentStateMachine(this);
    gameStates[startGameState->stateID_] = startGameState;
}

PlayerStateMachine::~PlayerStateMachine()
{
    for (const auto& state : gameStates)
        delete state.second;
}

// Reset cache (will force a log print)
void PlayerStateMachine::InvalidatePositionCache()
{
    prevPosCache[0] = std::numeric_limits<float>::lowest();
    prevPosCache[1] = std::numeric_limits<float>::lowest();
}

bool PlayerStateMachine::IsHost() { return isHost; }

void PlayerStateMachine::SetHost(bool host) { isHost = host; }

// Returns the mumble - ready position of the player
float PlayerStateMachine::GetMumblePos(int i) { return posCache[appSettings.audioCoordinateMap[i]]; }

// Returns the player's net ID
int PlayerStateMachine::GetNetID() { return netID; }

// Sets the player's net ID
void PlayerStateMachine::SetNetID(int id) { netID = id; }

// In mumble (0.0f, 0.0f) lets users hear each other better
void PlayerStateMachine::SetFullVolume()
{
    posCache[0] = 0.0f;
    posCache[1] = 0.0f;
}

void PlayerStateMachine::SetPos(int i, float pos)
{
    currentState->SetPos(i, pos);
}

// Will log the position, if needed
void PlayerStateMachine::TryLogPosition(bool force)
{
    // Only print the player position every so many frames, and if it has changed
    if (force || (++frameCounter > framesToPrintPosition && (
        std::abs(prevPosCache[0] - posCache[0]) > cachePosEpsilon ||
        std::abs(prevPosCache[1] - posCache[1]) > cachePosEpsilon
        )
        ))
    {
        frameCounter = 0;
        // Store the old position
        prevPosCache[0] = posCache[0];
        prevPosCache[1] = posCache[1];
        // Log the current player position to let the player know it is working
        if (mumbleLink.linkedMem != nullptr)
        {
            // Change log message based on if player is a ghost or not
            if (currentState->stateID_ == PlayerStateGhost::stateID_)
                logger.LogVariadic(LOG_CODE::MSG, true, "Linked - Ghost Position: (%.3f, %.3f)      ",
                    posCache[0], posCache[1]);
            else
                logger.LogVariadic(LOG_CODE::MSG, true, "Linked - Position: (%.3f, %.3f)      ",
                    posCache[0], posCache[1]);
        }
    }
}
