#include "EntityManager.h"


EntityManager::EntityManager() {

	init();
}

void EntityManager::init() {
	m_Entities.clear();
	m_EntityMap.clear();
	m_ToAdd.clear();
}

void EntityManager::update() {
	for (auto& e : m_ToAdd) {
		m_Entities.push_back(e);
		m_EntityMap[e->tag()].push_back(e);
	}
	m_ToAdd.clear();
	removeDeadEntities(m_Entities);
	for (auto& kvPair : m_EntityMap) {
		removeDeadEntities(kvPair.second);
	}
}

Entity* EntityManager::addEntity(const Entities::ID& tag) {
	std::unique_ptr<Entity> entity(
		new Entity(tag, m_TotalEntities++));
	Entity* ePtr = entity.get();
	m_ToAdd.push_back(std::move(entity));

	return ePtr;
}

void EntityManager::removeDeadEntities(RefEntityVec& v) {
	v.erase(
		std::remove_if(v.begin(), v.end(),
			[&](std::unique_ptr<Entity> obj) {
				return obj->IsActive() == false;
			}),
			v.end());
}

EntityManager::RefEntityVec& EntityManager::getEntities() {
	return m_Entities;
}

EntityManager::RefEntityVec& EntityManager::getEntities(const Entities::ID& tag) {
	return m_EntityMap[tag];
}