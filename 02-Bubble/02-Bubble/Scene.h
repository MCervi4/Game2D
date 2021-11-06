#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayerA.h"
#include "PlayerB.h"
#include "Menu.h"
#include "TexturedQuad.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(ShaderProgram game_texprogram, int lvl);
	void update(int deltaTime);
	void render();
	void switchGodmode();
	void setLevel(const int& lvl);

	float getPlayerAPosX();
	float getPlayerBPosX();

	float getPlayerAPosY();
	float getPlayerBPosY();

	float getPlayersPosX();
	float getPlayersPosY();

private:
	//void initShaders();

private:

	//Menu menu;

	TileMap* map1;
	TileMap* map2;
	TileMap* map3;
	Player* playerA;
	Player* playerB;
	ShaderProgram texProgram;
	//float currentTime;
	//glm::mat4 projection;


	int currentLevel;

};


#endif // _SCENE_INCLUDE