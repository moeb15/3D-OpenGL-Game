#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

#include "EntityManager.h"
#include "Scene.h"

class DefaultScene : public Scene {
private:
	EntityManager m_EM;
	std::shared_ptr<Entity> m_Player;
	std::shared_ptr<Entity> m_LightSource;
	std::shared_ptr<Entity> m_TestModel;
	glm::vec3 m_DirectionalLight;

public:
	DefaultScene(GameEngine* gameEngine);

	virtual void update(float);
	void spawnModel();
	void spawnPlayer();
	void buildScene();
	void spawnLightSource();

	virtual void sDoCommand(const Command&);
	virtual void sRender();
	void sMovement(float);
	void sCollision();
	void sLifespan(float);

private:
	void init();
	void spawnBullet(std::shared_ptr<Entity>&);
};

#endif // !DEFAULT_SCENE_H
