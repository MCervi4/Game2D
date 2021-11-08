#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT
};

void  Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {}

void  Player::update(int deltaTime) {
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap1, TileMap* tileMap2, TileMap* tileMap3)
{
	map1 = tileMap1;
	map2 = tileMap2;
	map3 = tileMap3;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

bool Player::getDamuntMeta() {
	return damuntMeta;
}

bool Player::isDeath() {
	return death;
}

void Player::switchGodmode() {
	godMode = !godMode;
	lavaWalk = !lavaWalk;
}

void Player::activateLavaWalk() {
	lavaWalk = true;
}

void Player::deactivateLavaWalk() {
	lavaWalk = false;
}

float Player::getPosX() {
	return posPlayer.x;
}

float Player::getPosY() {
	return posPlayer.y;
}

void Player::setLevelFinished() {
	levelFinished = true;
}


