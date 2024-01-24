#include "GameEngine.h"
#include "Scene.h"

void Scene::doCommand(Command cmd) {
	sDoCommand(cmd);
}

void Scene::registerCommand(int key, CommandTags::Name name) {
	m_CommandMap[key] = name;
}

std::unordered_map<int, CommandTags::Name>& Scene::getCommandMap() {
	return m_CommandMap;
}