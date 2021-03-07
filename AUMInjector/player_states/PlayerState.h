#pragma once

#include <map>
#include <iostream>

#define M_ASSERT(condition, message) do { if (! (condition)) { std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message << std::endl; std::terminate(); } } while (false)

class PlayerStateMachine;

class PlayerStateInterface
{
public:
	explicit PlayerStateInterface(unsigned ID);

	virtual ~PlayerStateInterface() = default;

	virtual void Update() {};

	virtual void OnEnter() {};

	virtual void OnExit() {};

	virtual void SetPos(int i, float pos);;

	virtual void TransferState(PlayerStateInterface* fromState) = 0;

	unsigned stateID_;

protected:
	virtual PlayerStateMachine* GetParentStateMachine() { return parentStateMachine_; }

private:
	friend class PlayerStateMachine;

	void SetParentStateMachine(PlayerStateMachine* parentStateMachine) { parentStateMachine_ = parentStateMachine; }

	PlayerStateMachine* parentStateMachine_;
};

template<typename ChildState>
class PlayerState : public PlayerStateInterface
{
public:
	PlayerState() : PlayerStateInterface(stateID_) {}

	~PlayerState() override = default;

	void TransferState(PlayerStateInterface* fromState)
	{
		M_ASSERT(stateTransfers[stateID_][fromState->stateID_] != nullptr, "Finite state link not found!");

		(dynamic_cast<ChildState*>(this)->*stateTransfers[stateID_][fromState->stateID_])(fromState);
	}

	static unsigned stateID_;

	static void RegisterLink(unsigned otherID, void (ChildState::* linkFunction)(PlayerStateInterface* from))
	{
		stateTransfers[stateID_][otherID] = linkFunction;
	}

	template<typename FromState>
	static void RegisterLink(void (ChildState::* linkFunction)(PlayerStateInterface* from))
	{
		stateTransfers[stateID_][PlayerState<FromState>::stateID_] = linkFunction;
	}

	void EmptyLink(PlayerStateInterface* from)
	{}

protected:
	static std::map<unsigned, std::map<unsigned, void (ChildState::*)(
		PlayerStateInterface* toState)>> stateTransfers;
};

unsigned GetNextId() noexcept;

template<typename ChildState>
std::map<unsigned, std::map<unsigned, void (ChildState::*)(
	PlayerStateInterface* toState)>> PlayerState<ChildState>::stateTransfers =
	std::map<unsigned, std::map<unsigned, void (ChildState::*)(
		PlayerStateInterface* toState)>>
	();

template<typename ChildState>
unsigned PlayerState<ChildState>::stateID_ = GetNextId();

