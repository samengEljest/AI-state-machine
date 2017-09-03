#ifndef MESSAGEDISPATCH_H
#define MESSAGEDISPATCH_H

#include "telgram.h"

#include <set>

#include <iostream>
using namespace std;

class Entity;
#define Dispatch MessageDispatch::Instance()


class MessageDispatch  ///< Singelton class
{
private:
	set<Telgram> PriorityQ; ///< container for delayed messages, sorted by dispatch time
	void discharge(Entity* receiver, const Telgram &msg); ///< calls an entity to handleMessage with a telgram(my message)

	MessageDispatch(){};
	MessageDispatch(const MessageDispatch&);
	MessageDispatch& operator=(const MessageDispatch&);

public:

	static MessageDispatch* Instance();

	void dispatchMessage(int Delay, int Sender, int Receiver, int Msg, void* ExtraInfo);  ///< creates a telgram, sets it in PriorityQ, calls discharge function
	void dispatchDelayedMassage();  ///< calld in updateGl in world, to see if there is an delayd message to be sent, if it is dispatches a message
};

#endif