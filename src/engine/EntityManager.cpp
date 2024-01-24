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

std::shared_ptr<Entity>& EntityManager::addEntity(const Entities::ID& tag) {
	std::shared_ptr<Entity> entity(
		new Entity(tag, m_TotalEntities++));
	m_ToAdd.push_back(entity);

	return entity;
}

void EntityManager::removeDeadEntities(EntityVec& v) {
	v.erase(
		std::remove_if(v.begin(), v.end(),
			[&](std::shared_ptr<Entity> obj) {
				return obj->IsActive() == false;
			}),
			v.end());
}

EntityManager::EntityVec& EntityManager::getEntities() {
	return m_Entities;
}

EntityManager::EntityVec& EntityManager::getEntities(const Entities::ID& tag) {
	return m_EntityMap[tag];
}