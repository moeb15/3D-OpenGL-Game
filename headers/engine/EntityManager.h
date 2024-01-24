#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vector>
#include <unordered_map>

class EntityManager {
public:
	typedef std::vector<std::unique_ptr<Entity>> EntityVec;
	typedef std::vector<std::unique_ptr<Entity>&> RefEntityVec;
	typedef std::unordered_map<Entities::ID, RefEntityVec> EntityMap;

private:
	RefEntityVec m_Entities;
	EntityMap m_EntityMap;
	EntityVec m_ToAdd;
	std::size_t m_TotalEntities;

	void init();
	
public:
	EntityManager();
	
	void update();
	void removeDeadEntities(RefEntityVec& v);
	Entity* addEntity(const Entities::ID& tag);
	RefEntityVec& getEntities();
	RefEntityVec& getEntities(const Entities::ID& tag);

};

#endif 