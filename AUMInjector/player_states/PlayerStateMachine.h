#pragma once

#include "PlayerState.h"
#include <limits>

class PlayerStateMachine
{
public:
	void InvalidatePositionCache();

	bool IsHost();

	void SetHost(bool host);

	// Returns the mumble-ready position of the player
	float GetMumblePos(int i);

	// In mumble (0.0f, 0.0f) lets users hear each other better
	void SetFullVolume();

	// Sets the position cache, class may choose to override this value
	void SetPos(int i, float pos);

	// Will log the position, if needed
	void TryLogPosition(bool force = false);

	// Returns the player's net ID
	int GetNetID();

	// Sets the player's net ID
	void SetNetID(int id);

	// On start communications sabotaged
	void StartCommunicationsSabotaged() { isCommunicationsSabotaged = true; }

	// On end communications sabotaged
	void EndCommunicationsSabotaged() { isCommunicationsSabotaged = false; }

	// Returns if communications is sabotaged
	bool IsCommunicationsSabotaged() { return isCommunicationsSabotaged; }

	// PosCacheReference
	float* GetPosCache() {
		return posCache;
	}

private:
	// Start old cache as an impossible limit, for first-frame printing
	float prevPosCache[2] = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };

	// Position difference threshold for printing
	const float cachePosEpsilon = 0.001f;

	// Position
	float posCache[3] = { 0.0f, 0.0f, 0.0f };

	// Counters for tracking when to print the position
	unsigned int frameCounter = 0;

	// Const for how often to print the position
	const unsigned int framesToPrintPosition = 15;

	// Cached player network id
	int netID = 0;

	bool isHost = false;

	bool isCommunicationsSabotaged;

	// -- State machine management --

public:
	explicit PlayerStateMachine(PlayerStateInterface* startGameState);

	virtual ~PlayerStateMachine();

	void AddState(PlayerStateInterface* state)
	{
		state->SetParentStateMachine(this);
		gameStates[state->stateID_] = state;
	}

	template<typename ToState>
	void TransferState()
	{
		M_ASSERT(gameStates.find(ToState::stateID_) != gameStates.end(), "Finite state link not found!");
		currentState->OnExit();
		gameStates[ToState::stateID_]->TransferState(currentState);
		currentState = gameStates[ToState::stateID_];
		currentState->OnEnter();
		previousStateID_ = ToState::stateID_;
	}

	void TransferToPreviousState()
	{
		M_ASSERT(gameStates.find(previousStateID_) != gameStates.end(), "Previous finite state link not found!");
		currentState->OnExit();
		gameStates[previousStateID_]->TransferState(currentState);
		currentState = gameStates[previousStateID_];
		currentState->OnEnter();
	}

	unsigned previousStateID_ = (std::numeric_limits<unsigned int>::max)();

	bool firstUpdate = true;

	void UpdateState()
	{
		//TODO: refactor this?
		if (firstUpdate)
		{
			firstUpdate = false;
			currentState->OnEnter();
		}

		currentState->Update();
	}

	unsigned GetCurrentStateID()
	{
		return currentState->stateID_;
	}

protected:
	PlayerStateInterface& GetCurrentState() const
	{
		return *currentState;
	}

private:
	PlayerStateInterface* currentState;
	std::map<unsigned, PlayerStateInterface*> gameStates;
};

extern PlayerStateMachine playerStateMachine;
