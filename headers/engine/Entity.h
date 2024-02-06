#ifndef ENTITY_H
#define ENTITY_H

#include "Components.h"
#include "EntityTags.h"
#include <tuple>
#include <memory>
#include <string>

class EntityManager;

typedef std::tuple<CTransform, CInput,
	CColor, CShader, 
	CHandle, CBoundingBox,
	CGravity, CState,
	CTexture, CModel,
	CLifespan, CMass,
	CDraggable> ComponentTuple;

class Entity {
	friend class EntityManager;
private:
	Entities::ID m_Tag = Entities::Default;
	bool m_Active = true;
	std::size_t m_ID = 0;
	ComponentTuple m_Components;

	Entity(const Entities::ID& tag, const std::size_t& id);

public:
	void destroy();
	bool IsActive() const;
	const Entities::ID& tag() const;
	std::size_t id() const;

	template<typename T, typename... TArgs>
	void addComponent(TArgs&&... mArgs) {
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
	}

	template<typename T>
	T& getComponent() {
		return std::get<T>(m_Components);
	}

	template<typename T>
	bool hasComponent() {
		return getComponent<T>().has;
	}
};

#endif 
