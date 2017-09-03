#ifndef MOUTHMANAGER_H
#define MOUTHMANAGER_H
#include <map>
#include <cassert>
#include <string>

using namespace std;

class Entity;

#define Manager Mouth_Manager::Instance()


class Mouth_Manager ///<singelton class
{
private:
	typedef map<int, Entity*> MouthMap; ///< map to save entitys

private:
	MouthMap mouthMap;
	Mouth_Manager(){};

	Mouth_Manager(const Mouth_Manager&);
	Mouth_Manager& operator=(const Mouth_Manager&);

public:
	static Mouth_Manager* Instance();

	void registerMouth(Entity* newMouth); ///< saves the entity, the key is the entitys ID
	Entity* GetMouthFromID(int id)const; ///<  returns pointer to entity by using the chosen ID
	void removeMouth(Entity* Entity); ///<  erase the Entity from map
};


#endif