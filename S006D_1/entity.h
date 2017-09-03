#ifndef ENTITY_H
#define ENTITY_H

#include <cassert>
#include <string>
#include <telgram.h>

class Entity
{
private:
	int ID;
	int currentTime;
	static int nextID;
	void setID(int val); ///<sets the ID of the entity to identify for messages

public:
	Entity(int id); ///<constructor
	virtual void update(int timer)=0; ///< virutal funktion that mouthbreather uses to update
	virtual bool handleMessage(const Telgram& message)=0; ///< virutal funktion to handle messages used in mouthbreather
	int getID()const; ///< returns the ID off the entity
	void SetCurrentTime(int time); ///< sets the current in-game time to help with messages
	int getCurrentTime(); ///< returns the current in game time
};

#endif