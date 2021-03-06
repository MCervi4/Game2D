#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	TileMap* map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::getRecargar() {
	return recargar;
}

bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	int aux = 0;
	int auxCount;

	for (int j = 0; j < mapSize.y; j++)
	{
		auxCount = 0;

		for (int i = 0; auxCount < mapSize.x; i++)
		{

			fin.get(tile);
			if (tile != ',') {
				if (tile != ' ') {
					aux *= 10;
					aux += tile - '0';
				}
			}
			else {
				if (aux == 0) map[j * mapSize.x + auxCount] = aux;
				else map[j * mapSize.x + auxCount] = aux + 1;
				auxCount++;
				aux = 0;
			}


		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + 20) / (tileSize);
	y0 = (pos.y -2 ) / tileSize;
	y1 = (pos.y + size.y) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + 20 + size.x) / tileSize;
	y0 = (pos.y - 2) / tileSize;
	y1 = (pos.y + size.y) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveDownA(const glm::ivec2& pos, const glm::ivec2& size, int* posY, bool &damuntMeta) const
{
	int x0, x1, y;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + 20 + size.x) / tileSize;
	y = ((pos.y + size.y) / tileSize);
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			
			if (map[y * mapSize.x + x] == 81) damuntMeta = true;
			else damuntMeta = false;

			if (*posY - tileSize * y  <= 4)
			{
				*posY = tileSize * y - size.y - 4 ;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveDownB(const glm::ivec2& pos, const glm::ivec2& size, int* posY, bool& damuntMeta) const
{

	int x0, x1, y;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + 20 + size.x) / tileSize;
	y =   ((pos.y - 2 ) / tileSize) ;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (map[y * mapSize.x + x] == 153) damuntMeta = true;
			else damuntMeta = false;

			if (*posY  - tileSize * y  >= -4)
			{
				*posY  += 4;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveUpA(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + size.x + 20) / tileSize;
	y = (pos.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{ 
		if (map[y * mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveUpB(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + size.x + 20) / tileSize;
	y = (pos.y + size.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::deathcollisionA(const glm::ivec2& pos, const glm::ivec2& size, const bool& godMode, const bool& lavaWalk) const
{
	if (godMode) return false;

	int x0, x1, y0, y1;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + size.x + 20) / tileSize;
	y0 = (pos.y) / tileSize;
	y1 = (pos.y + size.y) / tileSize;

	for (int x = x0; x <= x1; x++)
	{
		if (map[y0 * mapSize.x + x] != 0 || map[y1 * mapSize.x + x] != 0) {
			if (lavaWalk && map[y1 * mapSize.x + x]) {}
			else return true;
		}
	}

	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x0] != 0 || map[y * mapSize.x + x1] != 0) return true;
	}

	return false;
}

bool TileMap::deathcollisionB(const glm::ivec2& pos, const glm::ivec2& size, const bool& godMode, const bool& lavaWalk) const
{
	if (godMode) return false;

	int x0, x1, y0, y1;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + size.x + 20) / tileSize;
	y0 = (pos.y) / tileSize;
	y1 = (pos.y + size.y) / tileSize;

	for (int x = x0; x <= x1; x++)
	{
		if (map[y0 * mapSize.x + x] != 0 || map[y1 * mapSize.x + x] != 0) {
			if (lavaWalk && map[y0 * mapSize.x + x]) {}
			else return true;
		}
	}

	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x0] != 0 || map[y * mapSize.x + x1] != 0) return true;
	}

	return false;
}

bool TileMap::lavaWalkA(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const {
	int x0, x1, y;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + 20 + size.x) / tileSize;
	y = ((pos.y + size.y) / tileSize);
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 105)
		{

			if (*posY - tileSize * y <= 4)
			{
				*posY = tileSize * y - size.y - 4;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::lavaWalkB(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const {
	int x0, x1, y;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + 20 + size.x) / tileSize;
	y = ((pos.y - 2) / tileSize);
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 129)
		{

			if (*posY - tileSize * y >= -4)
			{
				*posY += 4;
				return true;
			}
		}
	}

	return false;
}

void TileMap::gemcollision(const glm::ivec2& pos, const glm::ivec2& size, float& saltAlt, bool& lavaWalk) {

	int x0, x1, y0, y1;

	x0 = (pos.x + 20) / tileSize;
	x1 = (pos.x + size.x + 20) / tileSize;
	y0 = (pos.y) / tileSize;
	y1 = (pos.y + size.y) / tileSize;

	for (int x = x0; x <= x1; x++)
	{
		if (map[y0 * mapSize.x + x] == 5 || map[y1 * mapSize.x + x] == 5) {
			saltAlt *= 2;
			map[y0 * mapSize.x + x] = 0;
			map[y1 * mapSize.x + x] = 0;
			recargar = true;

		}
		if (map[y0 * mapSize.x + x] == 4 || map[y1 * mapSize.x + x] == 4) {
			lavaWalk = true;
			map[y0 * mapSize.x + x] = 0;
			map[y1 * mapSize.x + x] = 0;
			recargar = true;
		}


	}

	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x0] == 5 || map[y * mapSize.x + x1] == 5) {
			saltAlt *= 2;
			map[y * mapSize.x + x0] = 0;
			map[y * mapSize.x + x1] = 0;
			recargar = true;

		}
		if (map[y * mapSize.x + x0] == 4 || map[y * mapSize.x + x1] == 4) {
			lavaWalk = true;
			map[y * mapSize.x + x0] = 0;
			map[y * mapSize.x + x1] = 0;
			recargar = true;
		}
	}

	
}