#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

#include "EntityManager.h"
#include "Scene.h"

class DefaultScene : public Scene {
private:
	EntityManager m_EM;
	std::shared_ptr<Entity> m_Player;
	std::shared_ptr<Entity> m_LightSource;

public:
	DefaultScene(GameEngine* gameEngine);

	virtual void update(float);
	void spawnPlayer();
	void buildScene();
	void spawnLightSource();

	virtual void sDoCommand(const Command&);
	virtual void sRender();
	void sMovement(float);
	void sCollision();

private:
	void init();
};

#endif // !DEFAULT_SCENE_H
