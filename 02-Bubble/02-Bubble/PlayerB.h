#ifndef _PLAYERB_INCLUDE
#define _PLAYERB_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class PlayerB : public Player
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap1, TileMap* tileMap2, TileMap* tileMap3);
	void setPosition(const glm::vec2& pos);



};


#endif // _PLAYERB_INCLUDE

