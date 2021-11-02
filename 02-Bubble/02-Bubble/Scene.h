#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayerA.h"
#include "PlayerB.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void loadLevel(int level);
	void update(int deltaTime);
	void render();
	void switchGodmode();
	void setLevel(const int& lvl);

private:
	void initShaders();

private:
	TileMap* map1;
	TileMap* map2;
	TileMap* map3;
	Player* playerA;
	Player* playerB;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	int currentLevel;

};


#endif // _SCENE_INCLUDE
