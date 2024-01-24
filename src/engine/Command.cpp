#include "Command.h"


Command::Command():
	m_Name(CommandTags::Name::Default),
	m_Type(CommandTags::Type::None),
	m_MousePos(0){}

Command::Command(const CommandTags::Name& name, const CommandTags::Type& type):
	m_Name(name),
	m_Type(type),
	m_MousePos(0){}

Command::Command(const CommandTags::Name& name, const CommandTags::Type& type, const glm::vec2& pos) :
	m_Name(name),
	m_Type(type),
	m_MousePos(pos) {}

const CommandTags::Name& Command::getName() const {
	return m_Name;
}

const CommandTags::Type& Command::getType() const {
	return m_Type;
}

const glm::vec2& Command::getMousePos() const {
	return m_MousePos;
}
