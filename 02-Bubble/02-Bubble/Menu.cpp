#include "Menu.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Menu::init(ShaderProgram& shaderProgram) {
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };


	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs[0].loadFromFile("images/BG_FAR.png", TEXTURE_PIXEL_FORMAT_RGBA);

	boto.init(shaderProgram, 0.f, 0.f, 1.f, 1.f);
	//currentTime = 0.0f;

	//spritesheet.loadFromFile("images/image.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	//background = Sprite::createSprite(glm::ivec2(704, 512), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	//background->setPosition(glm::vec2(0.0f, 0.0f));
}


void Menu::render() {
	//background->render();
	texQuad[0]->render(texs[0]);
	boto.render();
}

int Menu::whereToGo(int x, int y)
{
	if (boto.isPressed(x, y)) return 1;
	return 0;
}
