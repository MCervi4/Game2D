#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYERA_X_TILES 35
#define INIT_PLAYERA_Y_TILES 15

#define INIT_PLAYERB_X_TILES 35
#define INIT_PLAYERB_Y_TILES 38

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
	isFinal = false;
	
	string lvl = to_string(currentLevel);

	string loadedMap1 = "levels/level" + lvl + "1.txt";
	string loadedMap2 = "levels/level" + lvl + "2.txt";
	string loadedMap3 = "levels/level" + lvl + "3.txt";

	//BACKGROUND
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);

	map3 = TileMap::createTileMap(loadedMap3, glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //nomata
	map2 = TileMap::createTileMap(loadedMap2, glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //mata
	map1 = TileMap::createTileMap(loadedMap1, glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //terra

	playerA = new PlayerA();
	playerA->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playerA->setPosition(glm::vec2(INIT_PLAYERA_X_TILES * map1->getTileSize(), INIT_PLAYERA_Y_TILES * map1->getTileSize()));
	playerA->setTileMap(map1, map2, map3);

	playerB = new PlayerB();
	playerB->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playerB->setPosition(glm::vec2(INIT_PLAYERB_X_TILES * map1->getTileSize(), INIT_PLAYERB_Y_TILES * map1->getTileSize()));
	playerB->setTileMap(map1, map2, map3);

	

}



void Scene::update(int deltaTime, float iniW, float finW, float iniH, float finH)
{
		//currentTime += deltaTime;
		playerA->update(deltaTime);
		playerB->update(deltaTime);

		glm::vec2 geom[2] = { glm::vec2(iniW - 2, iniH - 2), glm::vec2(finW + 2, finH + 2) };
		glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);



		if (playerA->isDeath() || playerB->isDeath()) init(texProgram, currentLevel);

		if (playerA->getDamuntMeta() && playerB->getDamuntMeta()) {
			playerA->setLevelFinished();
			playerB->setLevelFinished();
			if (currentLevel == 5) isFinal = true;
			else  init(texProgram, ++currentLevel);
		}

		if (map3->getRecargar()) map3->prepareArrays(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
}

void Scene::render()
{
	texQuad->render(texs);

	map3->render();
	map2->render();
	map1->render();
	
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

float Scene::getPlayerAPosX() {
	return playerA->getPosX();
}

float Scene::getPlayerBPosX() {
	return playerB->getPosY();
}

float Scene::getPlayerAPosY() {
	return playerA->getPosY();
}

float Scene::getPlayerBPosY() {
	return playerB->getPosY();
}

float Scene::getPlayersPosX() {
	return (playerA->getPosX() + playerB->getPosX()) / 2.f;
}

float Scene::getPlayersPosY() {
	return (playerA->getPosY() + playerB->getPosY()) / 2.f;

}

bool Scene::getFinal()
{
	return isFinal;
}