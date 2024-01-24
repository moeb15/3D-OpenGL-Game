#ifndef SCENE_H
#define SCENE_H

#include "EntityManager.h"
#include "Command.h"
#include <unordered_map>
#include <GLFW/glfw3.h>

class GameEngine;

class Scene {
protected:
	GameEngine* m_Engine;
	std::unordered_map<int, CommandTags::Name> m_CommandMap;

public:
	Scene(GameEngine* engine):
		m_Engine(engine),
		m_CommandMap() {}

	virtual void update(float dt) = 0;
	virtual void sDoCommand(const Command&) = 0;
	virtual void sRender() = 0;
	
	std::unordered_map<int, CommandTags::Name>& getCommandMap();
	void doCommand(Command);
	void registerCommand(int, CommandTags::Name);

};

#endif 
