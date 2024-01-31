#ifndef ENTITY_TAGS_H
#define ENTITY_TAGS_H

namespace Entities {
	enum ID {
		Default,
		Player,
		Box,
		LightSoruce,
		TestModel,
		Bullet,
	};
}


namespace EntityState {
	enum ID {
		Ground,
		Air,
		None,
	};
}

#endif 