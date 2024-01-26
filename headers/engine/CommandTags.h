#ifndef COMMAND_TAGS_H
#define COMMAND_TAGS_H

namespace CommandTags {
	enum Type {
		Start,
		Stop,
		None,
	};

	enum Name {
		Up,
		Down,
		Left,
		Right,
		Forward,
		Backward,
		Jump,
		Select,
		Quit,
		ToggleCamera,
		Default,
	};
}

#endif // !COMMAND_TAGS_H

