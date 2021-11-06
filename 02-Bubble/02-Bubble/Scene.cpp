#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYERA_X_TILES 8
#define INIT_PLAYERA_Y_TILES 7

#define INIT_PLAYERB_X_TILES 8
#define INIT_PLAYERB_Y_TILES 20

Scene::Scene()
{
	map1 = NULL;
	map2 = NULL;
	map3 = NULL;
	playerA = NULL;
	playerB = NULL;
}

Scene::~Scene()
{
	if (map1 != NULL)
		delete map1;
	if (map2 != NULL)
		delete map2;
	if (map3 != NULL)
		delete map3;
	if (playerA != NULL)
		delete playerA;
	if (playerB != NULL)
		delete playerB;
}


void Scene::init(ShaderProgram game_texprogram, int level)
{
	texProgram = game_texprogram;
	currentLevel = level;
	
	string lvl = to_string(currentLevel);

	string loadedMap1 = "levels/level" + lvl + "1.txt";
	string loadedMap2 = "levels/level" + lvl + "2.txt";
	string loadedMap3 = "levels/level" + lvl + "3.txt";

	map1 = TileMap::createTileMap(loadedMap1, glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //terra
	map2 = TileMap::createTileMap(loadedMap2, glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //mata
	map3 = TileMap::createTileMap(loadedMap3, glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //nomata

	playerA = new PlayerA();
	playerA->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playerA->setPosition(glm::vec2(INIT_PLAYERA_X_TILES * map1->getTileSize(), INIT_PLAYERA_Y_TILES * map1->getTileSize()));
	playerA->setTileMap(map1, map2, map3);

	playerB = new PlayerB();
	playerB->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playerB->setPosition(glm::vec2(INIT_PLAYERB_X_TILES * map1->getTileSize(), INIT_PLAYERB_Y_TILES * map1->getTileSize()));
	playerB->setTileMap(map1, map2, map3);

}



void Scene::update(int deltaTime)
{
		//currentTime += deltaTime;
		playerA->update(deltaTime);
		playerB->update(deltaTime);

		if (playerA->isDeath() || playerB->isDeath()) init(texProgram, currentLevel);

		if (playerA->getDamuntMeta()) {
			if (currentLevel == 5) init(texProgram, currentLevel = 1);
			else  init(texProgram, ++currentLevel);
		}
}

void Scene::render()
{
	/*glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);*/

	map1->render();
	map2->render();
	map3->render();
	playerA->render();
	playerB->render();
}



void Scene::switchGodmode() {
	playerA->switchGodmode();
	playerB->switchGodmode();
}

void Scene::setLevel(const int& lvl) {
	currentLevel = lvl;
}

