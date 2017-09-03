#ifndef TELGRAM_H
#define TELGRAM_H

#include <math.h>
#include <iostream>

struct Telgram
{
	int sender; ///< the one sends the telgram
	int receiver; ///< the one that receive the the telgram
	int msg; ///< enum messeges in messageTypes.h
	int dispatchTime; ///< the time the message shoud be dispatched
	void* extraInfo; ///< additional info that, like place to be in
	Telgram()  ///< defoult constructor for Telgram
	{
		dispatchTime = -1;
		sender = -1;
		receiver = -1;
		msg = -1;
	}
	Telgram(int Time, int Sender, int Receiver, int Msg, void* Info = NULL)  ///< constructorr to create a Telgram with serten data
	{
		dispatchTime = Time;
		sender = Sender;
		receiver = Receiver;
		msg = Msg;
		extraInfo = Info;
	}
};

const double SmallestDelay = 0.25;


inline bool operator==(const Telgram& t1, const Telgram& t2)
{
	return ((t1.dispatchTime-t2.dispatchTime) < SmallestDelay) && //fabs but got error
			(t1.sender == t2.sender)        &&
			(t1.receiver == t2.receiver)    &&
			(t1.msg == t2.msg);
}

inline bool operator<(const Telgram& t1, const Telgram& t2)
{
	if (t1 == t2)
		return false;
	else
		return  (t1.dispatchTime < t2.dispatchTime);
}

inline std::ostream& operator<<(std::ostream& os, const Telgram& t)
{
	os << "time: " << t.dispatchTime << "  Sender: " << t.sender
	<< "   Receiver: " << t.receiver << "   Msg: " << t.msg;

	return os;
}

template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}

#endif