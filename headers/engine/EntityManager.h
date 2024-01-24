#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vector>
#include <unordered_map>

class EntityManager {
public:
	typedef std::vector<std::shared_ptr<Entity>> EntityVec;
	typedef std::unordered_map<Entities::ID, EntityVec> EntityMap;

private:
	EntityVec m_Entities;
	EntityMap m_EntityMap;
	EntityVec m_ToAdd;
	std::size_t m_TotalEntities;

	void init();
	
public:
	EntityManager();
	
	void update();
	void removeDeadEntities(EntityVec& v);
	std::shared_ptr<Entity>& addEntity(const Entities::ID& tag);
	EntityVec& getEntities();
	EntityVec& getEntities(const Entities::ID& tag);

};

#endif 