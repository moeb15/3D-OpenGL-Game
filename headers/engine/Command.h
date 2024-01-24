#ifndef COMMAND_H
#define COMMAND_H

#include "CommandTags.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Command {
private:
	CommandTags::Name m_Name;
	CommandTags::Type m_Type;
	glm::vec2 m_MousePos;

public:
	Command();
	Command(const CommandTags::Name& name, const CommandTags::Type& type);
	Command(const CommandTags::Name& name, const CommandTags::Type& type, const glm::vec2& pos);

	const CommandTags::Name& getName() const;
	const CommandTags::Type& getType() const;
	const glm::vec2& getMousePos() const;

};

#endif // !COMMAND_H

