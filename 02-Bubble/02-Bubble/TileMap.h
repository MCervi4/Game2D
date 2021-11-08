#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);
	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDownA(const glm::ivec2& pos, const glm::ivec2& size, int* posY, bool& damuntMeta) const;
	bool collisionMoveDownB(const glm::ivec2& pos, const glm::ivec2& size, int* posY, bool& damuntMeta) const;
	bool collisionMoveUpA(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveUpB(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool deathcollisionA(const glm::ivec2& pos, const glm::ivec2& size, const bool& godMode, const bool& lavaWalk) const;
	bool deathcollisionB(const glm::ivec2& pos, const glm::ivec2& size, const bool& godMode, const bool& lavaWalk) const;
	bool lavaWalkA(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool lavaWalkB(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;

	void gemcollision(const glm::ivec2& pos, const glm::ivec2& size, float& saltAlt, bool& lavaWalk);

	bool getRecargar();
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:

	bool loadLevel(const string& levelFile);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;

	bool recargar;

};


#endif // _TILE_MAP_INCLUDE
