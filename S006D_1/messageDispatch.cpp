#include "messageDispatch.h"
#include "mouth_Manager.h"
#include "messageTypes.h"
#include "entity.h"



MessageDispatch* MessageDispatch::Instance()
{
  static MessageDispatch instance;
  return &instance;
}


void MessageDispatch::discharge(Entity* reciver, const Telgram& telgram)
{
	if(!reciver->handleMessage(telgram))
	{
		cout << endl << "Message not handled";
	}
}

void MessageDispatch::dispatchMessage(int Delay, int Sender, int Receiver, int Msg, void* ExtraInfo)
{
	Entity* sender = Manager->GetMouthFromID(Sender);
	Entity* receiver = Manager->GetMouthFromID(Receiver);
	if(Receiver == NULL)
	{
		cout << "warning! no receiver with id " << Receiver;
		return;
	}
	Telgram telgram(0 ,Sender,Receiver,Msg,ExtraInfo);

	PriorityQ.insert(telgram);

	if (Delay <= 0)
	{
		cout << endl << "Message sent with no delay by " << sender->getID() << " to " << receiver->getID() << " with the Msg " << MsgToStr(Msg);
		discharge(receiver, telgram);
	}
	else
	{
		int currentTime = sender->getCurrentTime();
		telgram.dispatchTime = currentTime + Delay;
		PriorityQ.insert(telgram);
	}
}

void MessageDispatch::dispatchDelayedMassage()
{
	int currentTime = Manager->GetMouthFromID(1)->getCurrentTime(); //fuling för att få tiden

	while (!PriorityQ.empty() && PriorityQ.begin()->dispatchTime < currentTime && PriorityQ.begin()->dispatchTime > 0)
	{
		const Telgram& telgram = *PriorityQ.begin(); //takes first telgram in queue
		Entity* reciver = Manager->GetMouthFromID(telgram.receiver); // find entity to recive msg
		discharge(reciver, telgram);
		PriorityQ.erase(PriorityQ.begin()); //removes the sent message from queue
	}
}