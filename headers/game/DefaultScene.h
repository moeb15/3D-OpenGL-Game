#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

#include "EntityManager.h"
#include "Scene.h"

class DefaultScene : public Scene {
private:
	EntityManager m_EM;
	std::shared_ptr<Entity> m_Player;
	//std::shared_ptr<Entity> m_LightSource;
	std::shared_ptr<Entity> m_TestModel;
	glm::vec3 m_DirectionalLight;
	bool m_Paused;
	std::size_t m_LightSourceCount = 0;
	glm::vec3 m_LightColor = glm::vec3(1.0);


public:
	DefaultScene(GameEngine* gameEngine);

	virtual void update(float);
	void spawnModel(glm::vec3&);
	void spawnPlayer();
	void spawnBox(const glm::vec3&);;
	void buildScene();
	void spawnLightSource(const glm::vec3& pos = glm::vec3(0,10,0));
	void loadResources();

	virtual EntityManager::EntityVec& getSceneEntities();
	virtual void sDoCommand(const Command&);
	virtual void sRender();
	void sMovement(float);
	void sCollision();
	void sLifespan(float);
	void sDraggable();
	virtual void addToScene(Entities::ID, glm::vec3);
private:
	void init();
	void spawnBullet(std::shared_ptr<Entity>&);
};

#endif // !DEFAULT_SCENE_H
