#ifndef MOUTHSTATE_H
#define MOUTHSTATE_H

#include "state.h"

#include <stdlib.h>
#include <iostream>
using namespace std;

class Mouth_Breather;
struct Telgram;

 ///< classes for the different sates that mouth_breather can be in
class HomeAndRaid : public State<Mouth_Breather> 
{
private:
	HomeAndRaid();
	HomeAndRaid(const HomeAndRaid&);
	HomeAndRaid& operator=(const HomeAndRaid&);

public:
	static HomeAndRaid* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};



///< go to macdonalds to reset food bar
class VisitMacdonalds : public State<Mouth_Breather>
{
private:
	VisitMacdonalds();
	VisitMacdonalds(const VisitMacdonalds&);
	VisitMacdonalds& operator=(const VisitMacdonalds&);

public:
	static VisitMacdonalds* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};


///< go to store and buy energy drinks
class BuyEnergyDrinks : public State<Mouth_Breather>
{
private:
	BuyEnergyDrinks();
	BuyEnergyDrinks(const BuyEnergyDrinks&);
	BuyEnergyDrinks& operator=(const BuyEnergyDrinks&);

public:
	static BuyEnergyDrinks* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};

///< to get money, when its about to go out; 
class BegForMoney : public State<Mouth_Breather>
{
private:
	BegForMoney();
	BegForMoney(const BegForMoney&);
	BegForMoney& operator=(const BegForMoney&);


public:
	static BegForMoney* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};

///< the persen is moving from one location to another
class Move : public State<Mouth_Breather>
{
private:
	Move();
	Move(const Move&);
	Move& operator=(const Move&);

public:
	static Move* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};

///< beg at moms house to get money
class BegAtMom : public State<Mouth_Breather>
{
private:
	BegAtMom();
	BegAtMom(const BegAtMom&);
	BegAtMom& operator=(const BegAtMom&);

public:
	static BegAtMom* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};

///< A state to let the mouth_breather, reset there sleep bar
class SleepAtHome : public State<Mouth_Breather>
{
private:
	SleepAtHome();
	SleepAtHome(const SleepAtHome&);
	SleepAtHome& operator=(const SleepAtHome&);

public:
	static SleepAtHome* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};

///< a state for messeging and meet friend at max location
class MeetFriendAtMax : public State<Mouth_Breather>
{
private:
	MeetFriendAtMax();
	MeetFriendAtMax(const MeetFriendAtMax&);
	MeetFriendAtMax& operator=(const MeetFriendAtMax&);

public:
	static MeetFriendAtMax* Instance();
	virtual void Enter(Mouth_Breather* mouth_Breather);
	virtual void Execute(Mouth_Breather* mouth_Breather);
	virtual void Exit(Mouth_Breather* mouth_Breather);
	virtual bool onMessage(Mouth_Breather* mouth_Breather, const Telgram& message);
};


#endif