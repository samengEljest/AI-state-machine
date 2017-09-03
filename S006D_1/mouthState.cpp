#include "mouthState.h"
#include "telgram.h"
#include "mouth_Breather.h"
#include "messageDispatch.h"
#include "messageTypes.h"


//------------------HomeAndRaid------------------------------
HomeAndRaid::HomeAndRaid()
{}
HomeAndRaid* HomeAndRaid::Instance()
{
	static HomeAndRaid instance;
	return &instance;
}
void HomeAndRaid::Enter(Mouth_Breather *mouth_breather)
{
	if(mouth_breather->getLocation() != "Apartments")
	{
		mouth_breather->changeLocation("Apartments");
		cout << endl << mouth_breather->getName() << ": " << "going home now";
		mouth_breather->getFSM()->changeState(Move::Instance());
	}
	else
	{
		cout << endl << mouth_breather->getName() << ": " << "playeing dem vidya gems";
	}

}
void HomeAndRaid::Execute(Mouth_Breather *mouth_breather)
{
	mouth_breather->updateStatsHome();
	bool stateChanged = false;
	if (mouth_breather->lowEnergy()) //if he is thursty, highest prioraty for now
	{
		if(!mouth_breather->drinkDrink())
		{
			cout << endl << mouth_breather->getName() << ": " <<"have to go ut now :(";
			mouth_breather->getFSM()->changeState(BuyEnergyDrinks::Instance());
			stateChanged = true;
		}
		else
		{
			cout << endl << mouth_breather->getName() << ": " << "new energy, only got some left:" << mouth_breather->getDrinks();
		}
	}
	if(!stateChanged && mouth_breather->hungry())
	{
		mouth_breather->getFSM()->changeState(VisitMacdonalds::Instance());
		stateChanged = true;
	}
	if(!stateChanged && mouth_breather->sleepy())
	{
		mouth_breather->getFSM()->changeState(SleepAtHome::Instance());
		stateChanged = true;
	}
}
void HomeAndRaid::Exit(Mouth_Breather *mouth_breather)
{}
bool HomeAndRaid::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Meet at Max? ";

		if(mouth_Breather->getMoney() > mouth_Breather->getPrizeofFood())
		{
			Dispatch->dispatchMessage(0, mouth_Breather->getID(), message.sender, msg_MaxYes, 0);
			cout << endl << mouth_Breather->getName() << ": " << "send message back: Well be there";
			mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
		}
		else
		{
			cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, no money";
		}
		return true;
	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Well be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }

	return false;
}

//------------------VisitMacdonalds------------------------------
VisitMacdonalds::VisitMacdonalds()
{}
VisitMacdonalds* VisitMacdonalds::Instance()
{
	static VisitMacdonalds instance;
	return &instance;
}
void VisitMacdonalds::Enter(Mouth_Breather *mouth_breather)
{
	if(mouth_breather->getLocation() != "Mcdonalds")
	{
		mouth_breather->changeLocation("Mcdonalds");
		cout << endl << mouth_breather->getName() << ": " << "its so far to walk to McDonalds :(";
		mouth_breather->getFSM()->changeState(Move::Instance());
	}
	else
	{
		int random = rand() % 40 + 30;
		mouth_breather->setWaitTime(random + mouth_breather->getTime());
	}

}
void VisitMacdonalds::Execute(Mouth_Breather *mouth_breather)
{
	//time here to wait for next update, and an if to see if raid time
	if (!mouth_breather->canBuyFood())
	{
		cout << endl << mouth_breather->getName() << ": " << "no money";
		int random = rand() % 100;
		if(random < 80)
		{
			mouth_breather->getFSM()->changeState(BegForMoney::Instance());
		}
		else
		{
			mouth_breather->getFSM()->changeState(BegAtMom::Instance());
		}
	}
	else
	{
		if (mouth_breather->getWaitTime() == mouth_breather->getTime())
		{
			mouth_breather->buyFood();
			cout << endl << mouth_breather->getName() << ": " << "eating some burgurs";
			mouth_breather->getFSM()->changeState(HomeAndRaid::Instance());
		}
	}
}
void VisitMacdonalds::Exit(Mouth_Breather *mouth_breather)
{}
bool VisitMacdonalds::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, eating";
		
		return true;
	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Well be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }
	return false;
}

//------------------BuyEnergyDrinks------------------------------
BuyEnergyDrinks::BuyEnergyDrinks()
{}
BuyEnergyDrinks* BuyEnergyDrinks::Instance()
{
	static BuyEnergyDrinks instance;
	return &instance;
}
void BuyEnergyDrinks::Enter(Mouth_Breather *mouth_breather)
{
	if(mouth_breather->getLocation() != "Coop")
	{
		mouth_breather->changeLocation("Coop");
		cout << endl << mouth_breather->getName() << ": " << "all ut of energy drinks, :(. have to buy some more at coop";
		mouth_breather->getFSM()->changeState(Move::Instance());
	}
	else
	{
		int random = rand() % 40 + 30;
		mouth_breather->setWaitTime(random + mouth_breather->getTime());
	}
}
void BuyEnergyDrinks::Execute(Mouth_Breather *mouth_breather)
{
	mouth_breather->updateStatsHome();
	if(!mouth_breather->canBuyDrinks())
	{
		cout << endl << mouth_breather->getName() << ": " << "no money on bank account";
		int random = rand() % 100;
		if(random < 80)
		{
			mouth_breather->getFSM()->changeState(BegForMoney::Instance());
		}
		else
		{
			mouth_breather->getFSM()->changeState(BegAtMom::Instance());
		}
	}
	else
	{
		if (mouth_breather->getWaitTime() == mouth_breather->getTime())
		{
			mouth_breather->buyDrinks();
			cout << endl << mouth_breather->getName() << ": " << "refreshing enegy drinks, going back now";
			mouth_breather->getFSM()->changeState(HomeAndRaid::Instance());
		}
	}
}
void BuyEnergyDrinks::Exit(Mouth_Breather *mouth_breather)
{}
bool BuyEnergyDrinks::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Meet at Max? ";

		if(mouth_Breather->getMoney() > mouth_Breather->getPrizeofFood())
		{
			Dispatch->dispatchMessage(0, mouth_Breather->getID(), message.sender, msg_MaxYes, 0);
			cout << endl << mouth_Breather->getName() << ": " << "send message back: Well be there";
			mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
		}
		else
		{
			cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, no money";
		}
		return true;
	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Well be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }
	return false;
}

//------------------BegForMoney------------------------------
BegForMoney::BegForMoney()
{}
BegForMoney* BegForMoney::Instance()
{
	static BegForMoney instance;
	return &instance;
}
void BegForMoney::Enter(Mouth_Breather *mouth_breather)
{
	if(mouth_breather->getLocation() != "City")
	{
		mouth_breather->changeLocation("City");
		cout << endl << mouth_breather->getName() << ": " << "going to the city to beg for mony ;)";
		mouth_breather->getFSM()->changeState(Move::Instance());
	}
	else
	{
		cout << endl << mouth_breather->getName() << ": " << "please sir, can i have some money, my family is starving, lol";
	}
}
void BegForMoney::Execute(Mouth_Breather *mouth_breather)
{
	mouth_breather->updateStatsWork();
	int random = rand() % 4 + 1;
	mouth_breather->increaseMoney(random);

	if(mouth_breather->getMoney() > 120)
	{
		cout << endl << mouth_breather->getName() << ": " << "got a lot of cash on the old bank account now";
		if(mouth_breather->hungry())
		{
			mouth_breather->getFSM()->changeState(VisitMacdonalds::Instance());
		}
		else if (mouth_breather->lowEnergy())
		{
			if(!mouth_breather->drinkDrink())
			{
				mouth_breather->getFSM()->changeState(BuyEnergyDrinks::Instance());
			}
		}
	}
}
void BegForMoney::Exit(Mouth_Breather *mouth_breather)
{}
bool BegForMoney::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Meet at Max? ";

		if(mouth_Breather->getMoney() > mouth_Breather->getPrizeofFood())
		{
			Dispatch->dispatchMessage(0, mouth_Breather->getID(), message.sender, msg_MaxYes, 0);
			cout << endl << mouth_Breather->getName() << ": " << "send message back: Well be there";
			mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
		}
		else
		{
			cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, no money";
		}
		return true;
	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Well be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }
	return false;
}

//------------------Move------------------------------
Move::Move()
{}
Move* Move::Instance()
{
	static Move instance;
	return &instance;
}
void Move::Enter(Mouth_Breather *mouth_breather)
{
	string loc = mouth_breather->getLocation();
	if(loc == "City")
	{
		mouth_breather->setArrival(400,470);
	}
	else if(loc == "Coop")
	{
		mouth_breather->setArrival(90,340);
	}
	else if(loc == "Mcdonalds")
	{
		mouth_breather->setArrival(330,240);
	}
	else if(loc == "Apartments")
	{
		mouth_breather->setArrival(60,80);
	}
	else if(loc == "Moms_House")
	{
		mouth_breather->setArrival(270,160);
	}
	else if(loc == "Max")
	{
		mouth_breather->setArrival(110,260);
	}
}
void Move::Execute(Mouth_Breather *mouth_breather)
{
	int nowX = mouth_breather->getX();
	int nowY = mouth_breather->getY();
	int arrX = mouth_breather->getArrivalX();
	int arrY = mouth_breather->getArrivalY();

	if(nowX != arrX)
	{
		if(nowX < arrX)
		{
			nowX += 2;
		}
		else
		{
			nowX -= 2;
		}
	}
	if(nowY != arrY)
	{
		if(nowY < arrY)
		{
			nowY += 2;
		}
		else
		{
			nowY -= 2;
		}
	}

	mouth_breather->setPosition(nowX, nowY);
	mouth_breather->move_IconButton(nowX, nowY);

	if(nowX == arrX && nowY == arrY)
	{
		//mouth_breather->getFSM()->changeState(mouth_breather->getFSM()->getPreviousState());
		string loc = mouth_breather->getLocation();
		if(loc == "City")
		{
			mouth_breather->getFSM()->changeState(BegForMoney::Instance());
		}
		else if(loc == "Coop")
		{
			mouth_breather->getFSM()->changeState(BuyEnergyDrinks::Instance());
		}
		else if(loc == "Mcdonalds")
		{
			mouth_breather->getFSM()->changeState(VisitMacdonalds::Instance());
		}
		else if(loc == "Apartments")
		{
			mouth_breather->getFSM()->changeState(HomeAndRaid::Instance());
		}
		else if(loc == "Moms_House")
		{
			mouth_breather->getFSM()->changeState(BegAtMom::Instance());
		}
		else if(loc == "Max")
		{
			mouth_breather->getFSM()->changeState(MeetFriendAtMax::Instance());
		}
		
	}
}
void Move::Exit(Mouth_Breather *mouth_breather)
{}
bool Move::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Meet at Max? ";

		if(mouth_Breather->getMoney() > mouth_Breather->getPrizeofFood())
		{
			Dispatch->dispatchMessage(0, mouth_Breather->getID(), message.sender, msg_MaxYes, 0);
			cout << endl << mouth_Breather->getName() << ": " << "send message back: Well be there";
			mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
		}
		else
		{
			cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, no money";
		}
		return true;
	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Well be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }

    return false; //send message to global message handler
}

//------------------BegAtMom------------------------------
BegAtMom::BegAtMom()
{}
BegAtMom* BegAtMom::Instance()
{
	static BegAtMom instance;
	return &instance;
}
void BegAtMom::Enter(Mouth_Breather *mouth_breather)
{
	if(mouth_breather->getLocation() != "Moms_House")
	{
		mouth_breather->changeLocation("Moms_House");
		cout << endl << mouth_breather->getName() << ": " << "I wonder if mom will let me \"borrow\" some money";
		mouth_breather->getFSM()->changeState(Move::Instance());
	}
	else
	{
		cout << endl << mouth_breather->getName() << ": " << "Hello my dear mother, how are you, can have have some money";
		int random = rand() % 60 + 30;
		mouth_breather->setWaitTime(random + mouth_breather->getTime());
	}
}
void BegAtMom::Execute(Mouth_Breather *mouth_breather)
{
	mouth_breather->updateStatsWork();
	if (mouth_breather->getWaitTime() == mouth_breather->getTime())
	{
		cout << endl << mouth_breather->getName() << ": " << "thx mom, i will totally pay you back this time";
		int random = rand() % 300 + 100;
		mouth_breather->increaseMoney(random);
		if(mouth_breather->hungry())
		{
			mouth_breather->getFSM()->changeState(VisitMacdonalds::Instance());
		}
		else if (mouth_breather->lowEnergy())
		{
			if(!mouth_breather->drinkDrink())
			{
				mouth_breather->getFSM()->changeState(BuyEnergyDrinks::Instance());
			}
		}
	}	
}
void BegAtMom::Exit(Mouth_Breather *mouth_breather)
{}
bool BegAtMom::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Meet at Max? ";

		if(mouth_Breather->getMoney() > mouth_Breather->getPrizeofFood())
		{
			Dispatch->dispatchMessage(0, mouth_Breather->getID(), message.sender, msg_MaxYes, 0);
			cout << endl << mouth_Breather->getName() << ": " << "send message back: Well be there";
			mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
		}
		else
		{
			cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, no money";
		}
		return true;
	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Well be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }
	return false;
}

//------------------SleepAtHome------------------------------
SleepAtHome::SleepAtHome()
{}
SleepAtHome* SleepAtHome::Instance()
{
	static SleepAtHome instance;
	return &instance;
}
void SleepAtHome::Enter(Mouth_Breather *mouth_breather)
{
	cout << endl << mouth_breather->getName() << ": " << "So sleepy, time for bed";
	mouth_breather->setWaitTime(60 + mouth_breather->getTime());
}
void SleepAtHome::Execute(Mouth_Breather *mouth_breather)
{
	mouth_breather->updateStatsHome();
	if (mouth_breather->getWaitTime() == mouth_breather->getTime())
	{
		mouth_breather->resetSleep();
		mouth_breather->getFSM()->changeState(HomeAndRaid::Instance());
		int random = rand() % 4 +1;
		while(mouth_breather->getID() == random)
		{	
			random = rand() % 4 + 1;
		}
		cout << endl << mouth_breather->getName() << ": " << "wake, waly. Send message: to " << random;
		Dispatch->dispatchMessage(0,mouth_breather->getID(), random, msg_MeetAtMax, 0);
	}

}
void SleepAtHome::Exit(Mouth_Breather *mouth_breather)
{}
bool SleepAtHome::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:

		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Meet at Max? ";
		cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, sleeping";

	case msg_MaxYes:
		cout << endl << mouth_Breather->getName() << ": " << "Message Recived: Will be there";
		mouth_Breather->getFSM()->changeState(MeetFriendAtMax::Instance());
    }
	return false;
}

//----------------------MeetFriendAtMax-------------------
MeetFriendAtMax::MeetFriendAtMax()
{}
MeetFriendAtMax* MeetFriendAtMax::Instance()
{
	static MeetFriendAtMax instance;
	return &instance;
}
void MeetFriendAtMax::Enter(Mouth_Breather* mouth_Breather)
{
	if(mouth_Breather->getLocation() != "Max")
	{
		mouth_Breather->changeLocation("Max");
		cout << endl << mouth_Breather->getName() << ": " << "going to Max to meet my buddy";
		mouth_Breather->getFSM()->changeState(Move::Instance());
	}
	else
	{
		mouth_Breather->setWaitTime(120 + mouth_Breather->getTime());
	}
}
void MeetFriendAtMax::Execute(Mouth_Breather* mouth_Breather)
{
	if (mouth_Breather->getWaitTime() == mouth_Breather->getTime())
	{
		mouth_Breather->buyFood();
		cout << endl << mouth_Breather->getName() << ": " << "going from max now now, bye";
		mouth_Breather->getFSM()->changeState(HomeAndRaid::Instance());
	}
}
void MeetFriendAtMax::Exit(Mouth_Breather* mouth_Breather)
{}
bool MeetFriendAtMax::onMessage(Mouth_Breather *mouth_Breather, const Telgram &message)
{
	switch(message.msg)
    {
    case msg_MeetAtMax:
		cout << endl << mouth_Breather->getName() << ": " << "send message back: nope, eating";
		return true;
    }
	return false;
}