#include "entity.h"

int Entity::nextID = 0;

Entity::Entity(int id)
{
	setID(id);
}

int Entity::getID()const
{
	return this->ID;
}

void Entity::setID(int val)
{
	this->ID = val;
	this->nextID = ID++;
}

void Entity::SetCurrentTime(int time)
{
	this->currentTime = time;
}

int Entity::getCurrentTime()
{
	return this->currentTime;
}



