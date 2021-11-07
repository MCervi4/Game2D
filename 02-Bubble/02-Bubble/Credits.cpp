#include "Credits.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Credits::init(ShaderProgram& shaderProgram) {

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs.loadFromFile("images/credits_final.png", TEXTURE_PIXEL_FORMAT_RGBA);

	returnbut.init(shaderProgram, 10.f, 440.f, 100.f, 470.f, "images/return.png");

}


void Credits::render() {
	texQuad->render(texs);
	returnbut.render();
}
