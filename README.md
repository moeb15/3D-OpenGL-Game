# 3D Game Engine
For this project I'm developing a 3D game engine using C++, GLFW, and Opengl.
At the moment the following has been completed,

* ECS architectue for representing game world entities
* EntityManager factory class for creation and deletion of entities
* Resource manager for loading shaders, textures, and models
* Scene abstract class for all game scenes to inherit from
* Command class for representing input, commands are passed to and processed by the currently active scene
* Physics system, collision detection using AABB
* Models, models are loaded using Assimp
* Shader and Texture classes
* Raycasting
* Level editor (in-progress)
* GameEngine singleton class 

I'll be actively adding to and refining this project.