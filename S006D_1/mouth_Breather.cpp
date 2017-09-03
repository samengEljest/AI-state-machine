#include "mouth_Breather.h"

Mouth_Breather::Mouth_Breather(int ID, QPushButton *button, string name):Entity(ID)
{
	int random = rand() % 80 + 20;
	this->sleep = random;
	random = rand() % 30 + 150;
	this->money	= random;
	random = rand() % 14 + 2;
	this->drinks = random;
	random = rand() % 80 + 100;
	this->hunger = random;
	random = rand() % 80 + 100;
	this->energy = 100;
	this->prizeOfBurger = 60;
	this->prizeOfDrink = 50;
	this->changeLocation("Apartments");
	this->mb_Button = button;
	this->x = 60;
	this->y = 80;
	this->char_name = name;
	
	stateMachine = new StateMachine<Mouth_Breather>(this);
	stateMachine->setCurrentState(HomeAndRaid::Instance());
}


void Mouth_Breather::update(int time)
{
	this->time = time;
	this->SetCurrentTime(time);
	stateMachine->update();
}


bool Mouth_Breather::handleMessage(const Telgram& message)
{
	return stateMachine->handleMessage(message);
}

StateMachine<Mouth_Breather>* Mouth_Breather::getFSM()const
{
	return stateMachine;
}

//-------------------------------------------------
bool Mouth_Breather::lowEnergy()
{
	if(this->energy < 30)
		return true;
	else
		return false;
}
bool Mouth_Breather::hungry()
{
	if(this->hunger < 30)
		return true;
	else
		return false;
}
bool Mouth_Breather::sleepy()
{
	if(this->sleep < 20)
		return true;
	else
		return false;	
}

void Mouth_Breather::increaseMoney(int val)
{
	this->money += val; 
}

bool Mouth_Breather::canBuyFood()
{
	if ((money - prizeOfBurger) >= 0)
	{
		return true;
	}
	else
		return false;
}
bool Mouth_Breather::canBuyDrinks()
{
	if((money - prizeOfDrink) >= 0)
	{
		return true;
	}
	else
		return false;
}
void Mouth_Breather::buyDrinks()
{
	this->drinks += 19;
	this->money -= prizeOfDrink;
	this->energy = 100;
}
void Mouth_Breather::buyFood()
{
	this->hunger = 100;

	if(this->energy > 60)
		this->energy = 100;
	else
		this->energy += 40;

	this->money -= prizeOfBurger;
}
bool Mouth_Breather::drinkDrink()
{
	if(this->drinks > 0)
	{
		this->drinks--;
		this->energy = 100;
		this->sleep++;
		return true;
	}
	else
		return false;
}

void Mouth_Breather::resetSleep()
{
	this->sleep = 100;
}

void Mouth_Breather::decreaseHunger(int val)
{
	if(hunger - val < 0)
	{
		this->hunger = 0;
	}
	else
	{
		this->hunger -= val;
	}
}
void Mouth_Breather::decreaseEnergy(int val)
{
	if(energy - val < 0)
	{
		this->energy = 0;
	}
	else
	{
		this->energy -= val;
	}
}
void Mouth_Breather::decreaseSleep(int val)
{
	if(sleep - val < 0)
	{
		this->sleep = 0;
	}
	else
	{
		this->sleep -= val;
	}
}

int Mouth_Breather::getSleep()
{
	return this->sleep;
}
int Mouth_Breather::getDrinks()
{
	return this->drinks;
}
int Mouth_Breather::getEnergy()
{
	return this->energy;
}
int Mouth_Breather::getHunger()
{
	return this->hunger;
}
int Mouth_Breather::getMoney()
{
	return this->money;
}
int Mouth_Breather::getPrizeOfDrink()
{
	return this->prizeOfDrink;
}
int Mouth_Breather::getPrizeofFood()
{
	return this->prizeOfBurger;
}

string Mouth_Breather::getLocation()
{
	return this->location;
}
void Mouth_Breather::changeLocation(string loc)
{
	this->location = loc;
}
void Mouth_Breather::setPosition(int X, int Y)
{
	this->x = X;
	this->y = Y;
}
void Mouth_Breather::setArrival(int X, int Y)
{
	this->arrivalX = X;
	this->arrivalY = Y;
}

int Mouth_Breather::getX()
{
	return this->x;
}
int Mouth_Breather::getY()
{
	return this->y;
}
int Mouth_Breather::getArrivalX()
{
	return this->arrivalX;
}
int Mouth_Breather::getArrivalY()
{
	return this->arrivalY;
}

void Mouth_Breather::move_IconButton(int moveX, int moveY)
{
	this->mb_Button->setGeometry(moveX, moveY, 30, 30);
}

void Mouth_Breather::updateStatsHome()
{
	int random = rand() % 75;
	if (random > 50)
	{
		random = rand() % 6 + 1;
		this->decreaseEnergy(random);
	}
	random = rand() % 75;
	if (random > 50)
	{
		this->decreaseHunger(1);
	}
	if (random >= 70)
	{
		this->decreaseSleep(1);
	}
}
void Mouth_Breather::updateStatsWork()
{
	int random = rand() % 75;
	if (random >= 50)
	{
		this->decreaseEnergy(1);
	}
	random = rand() % 75;
	if (random >= 50)
	{
		this->decreaseHunger(1);
	}
	random = rand() % 100;
	if (random >= 80)
	{
		this->decreaseSleep(2);
	}
}

int Mouth_Breather::getTime()
{
	return this->time;
}
int Mouth_Breather::getWaitTime()
{
	return this->waitTime;
}

void Mouth_Breather::setWaitTime(int wait)
{
	this->waitTime = wait;
}

string Mouth_Breather::getName()
{
	return this->char_name;
}

