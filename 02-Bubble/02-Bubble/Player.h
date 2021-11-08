#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap1, TileMap* tileMap2, TileMap* tileMap3);
	void setPosition(const glm::vec2& pos);
	void switchGodmode();
	void activateLavaWalk();
	void deactivateLavaWalk();
	void setLevelFinished();

	bool getDamuntMeta();
	bool isDeath();

	float getPosX();
	float getPosY();


protected:
	bool bJumping, damuntMeta, death, godMode, lavaWalk, saltAlt, levelFinished;

	float jumpH;

	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map1; //Terra
	TileMap* map2; //Mata
	TileMap* map3; //NoMata


};


#endif // _PLAYER_INCLUDE