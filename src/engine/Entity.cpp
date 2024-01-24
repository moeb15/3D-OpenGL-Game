#include "Entity.h"


Entity::Entity(const Entities::ID& tag,
	const std::size_t& id):
	m_Tag(tag),
	m_ID(id),
	m_Active(true) {}

void Entity::destroy() {
	m_Active = false;
}

bool Entity::IsActive() const {
	return m_Active;
}

const Entities::ID& Entity::tag() const {
	return m_Tag;
}

const std::size_t& Entity::id() const {
	return m_ID;
}