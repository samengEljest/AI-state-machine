#include "mouth_Manager.h"
#include "entity.h"

Mouth_Manager* Mouth_Manager::Instance()
{
	static Mouth_Manager instance;
	return &instance;
}

Entity* Mouth_Manager::GetMouthFromID(int id)const
{
	MouthMap::const_iterator ent = mouthMap.find(id);
	return ent->second;
}

void Mouth_Manager::removeMouth(Entity* mouth_breather)
{
	mouthMap.erase(mouthMap.find(mouth_breather->getID()));
}

void Mouth_Manager::registerMouth(Entity* newMouth)
{
	mouthMap.insert(make_pair(newMouth->getID(), newMouth));
}
