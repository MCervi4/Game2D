#include "Instructions.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Instructions::init(ShaderProgram& shaderProgram) {

	//BACKGROUND
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs[0].loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//INSTR1
	geom[0].x = 40.f;
	geom[0].y = 20.f;
	geom[1].x = 290.f;
	geom[1].y = 420.f;


	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs[1].loadFromFile("images/instr.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//INSTR2
	geom[0].x = 340.f;
	geom[0].y = 20.f;
	geom[1].x = 590.f;
	geom[1].y = 420.f;


	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs[2].loadFromFile("images/instr2.png", TEXTURE_PIXEL_FORMAT_RGBA);


	returnbut.init(shaderProgram, 10.f, 440.f, 100.f, 470.f, "images/return.png");

}


void Instructions::render() {
	texQuad[0]->render(texs[0]);
	texQuad[1]->render(texs[1]);
	texQuad[2]->render(texs[2]);
	returnbut.render();
}
