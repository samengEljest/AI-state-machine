#ifndef MOUTHBREATHER_H
#define MOUTHBREATHER_H

#include <string>
#include <cassert>
#include <qpushbutton>
#include <iostream>

#include "mouthState.h"
#include "entity.h"
#include "stateMachine.h"


using namespace std;

template <class entity_type> class State;
struct Telgram;

const int maxDrinks = 20;
const int MaxEnergyLevel = 100;
const int MaxHungerLevel = 100;
const int MaxSleep = 100;


class Mouth_Breather : public Entity
{

private:
	StateMachine<Mouth_Breather>* stateMachine;

	string location;

	int energy; //higher value, less energy
	int hunger; //higher value, more hungrey
	int drinks;
	int money; //less money == bad
	int prizeOfDrink;
	int sleep;
	int prizeOfBurger;
	int x,y, arrivalX, arrivalY;
	int time, waitTime;
	string char_name;

	QPushButton *mb_Button; ///< a QPushButten pointer so we can set the position of the entity on the screen
	
public:
	StateMachine<Mouth_Breather>* getFSM()const; ///<returns the state machine to be able change and get states

	Mouth_Breather(int ID, QPushButton *button, string name); ///< constructor of the mouthbreather, sets random data to energy,hunger,drinks and so on

	void update(int time); ///< done every frame. sets the time and calls update funktion from stateMahine
	virtual bool handleMessage(const Telgram& message); ///< calls stateMachines funktion handlemessage

	int getPrizeOfDrink(); ///< returns the prizeOfDrink
	int getPrizeofFood(); ///< returns the PrizeofFood
	int getEnergy(); ///< returns the energy
	int getHunger();///< returns the hunger
	int getDrinks(); ///< returns the drinks
	int getMoney(); ///< returns the money
	int getTime(); ///< returns the time
	int getWaitTime(); ///< returns the waittime
	int getSleep(); ///< returns the sleep
	string getName(); ///< returns the name

	void setWaitTime(int wait); ///< sets the waitTime to how many fraims we shall stay at a serten state

	void decreaseHunger(int val);  ///< decrease hunger
	void decreaseEnergy(int val); ///< decrease energy
	void decreaseSleep(int val); ///< decrease sleep

	bool drinkDrink(); ///< -drink, resetEnergy
	bool canBuyDrinks(); ///< returns true if we have enouth money
	bool canBuyFood(); ///< returns true if we have enouth money
	void buyDrinks(); ///< -money, +drinks
	void buyFood(); ///< resetHunger, -money, +energy
	void resetSleep(); ///< sets sleep to 100
	
	void increaseMoney(int val);///< money+

	bool lowEnergy(); ///< returns true if energy is below 30
	bool hungry(); ///< returns true if hunger is below 30
	bool sleepy(); ///< returns true if sleep is below 20

	string getLocation(); ///< returns current location
	void changeLocation(string loc); ///< sets the location to loc

	void setPosition(int X, int Y); ///< sets new x and y cordinets for the ,outh_breathers position
	void setArrival(int X, int Y); ///< sets new x and y cordinates for the arrival position

	void updateStatsHome(); ///<  calls decreaseHunger, decreaseEnergy, decreaseSleep with random values
	void updateStatsWork(); ///<  calls decreaseHunger, decreaseEnergy, decreaseSleep with random values

	int getX(); ///< returns x position
	int getY(); ///< returns y position
	int getArrivalX(); ///< returns the arrival x position
	int getArrivalY(); ///< returns the arrival y position

	void move_IconButton(int moveX, int moveY); ///< sets the QPushButton the the current x and y cordinets, so it moves on the screen
};

#endif