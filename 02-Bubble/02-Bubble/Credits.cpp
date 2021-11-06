#include "Credits.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Credits::init(ShaderProgram& shaderProgram) {

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);



}


void Credits::render() {
	texQuad->render(texs);
}
