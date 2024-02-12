#ifndef RESOURCE_TAGS_H
#define RESOURCE_TAGS_H

namespace ResourceTags {
	enum Textures {
		PlayerDiffuse,
		PlayerSpecular,
		PlayerEmission,
		ContainerDiffuse,
		ContainerSpecular,
		ContainerEmission,
	};

	enum Shaders {
		DefaultShader,
		LightingShader,
		ModelShader,
		BulletShader,
	};

	enum Models {
		DefaultModel,
	};
}

#endif // !RESOURCE_TAGS_H

