#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <cassert>
#include <string>
#include "state.h"
#include "telgram.h"
using namespace std;

template <class entity_type>
class StateMachine
{
private:
	entity_type* owner; //Agent that owns the instance
	State<entity_type>* currentState; //Current state
	State<entity_type>* previousState; //Record of last state
	State<entity_type>* globalState; //The global state

public:
	StateMachine(entity_type* Owner)
	{
		owner = Owner;
		currentState = NULL;
		previousState = NULL;
		globalState = NULL;
	}

	virtual ~StateMachine(){}

	//methods to initialize the fsm
	void setCurrentState(State<entity_type>* state){currentState = state;}
	void setGlobalState(State<entity_type>* state){globalState = state;}
	void setPreviousState(State<entity_type>* state){previousState = state;}

	void update()const //update the fsm
	{
		if(globalState) globalState->Execute(owner);
		if (currentState) currentState->Execute(owner);
	}

	bool handleMessage(const Telgram& message)const
	{
		if (currentState && currentState->onMessage(owner, message))
			return true;
		if (globalState && globalState->onMessage(owner, message))
			return true;
		return false;
	}

	void changeState(State<entity_type>* NewState) //change to new state
	{
		previousState = currentState;
		currentState->Exit(owner);
		currentState = NewState;
		currentState->Enter(owner);
	}

	void PreviousState() {ChangeState(previousState);}

	bool isInState(const State<entity_type>& state)const
	{
		if(typeid(*currentState) == typeid(state))
			return true;
		return false;
	}

	State<entity_type>* getCurrentState() const{return currnetState;}
	State<entity_type>* getGlobalState() const{return globalState;}
	State<entity_type>* getPreviousState() const{return previousState;}

	string getNameOfCurrentState()const
	{
		string state(typeid(*currentState).name());
		if (state.size() > 5)
			state.erase(0,6);
		return state;
	}
};

#endif