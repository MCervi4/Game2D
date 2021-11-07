#include "Menu.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Menu::init(ShaderProgram& shaderProgram) {

	//BACKGROUND
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs.loadFromFile("images/background_title.png", TEXTURE_PIXEL_FORMAT_RGBA);


	//BUTTONS
	start.init(shaderProgram, 220.f, 220.f, 420.f, 280.f, "images/start.png");
	howtoplay.init(shaderProgram, 220.f, 300.f, 420.f, 360.f, "images/howtoplay.png");
	levels.init(shaderProgram, 220.f, 380.f, 420.f, 440.f, "images/levels.png");
	exit.init(shaderProgram, 20.f, 410.f, 70.f, 460.f, "images/exit.png");


	
}


void Menu::render() {
	texQuad->render(texs);
	start.render();
	howtoplay.render();
	levels.render();
	exit.render();
}

int Menu::whereToGo(int x, int y)
{
	if (start.isPressed(x, y)) return 1;
	else if (howtoplay.isPressed(x, y)) return 2;
	else if (levels.isPressed(x, y)) return 3;
	else if (exit.isPressed(x, y)) return 4;
	return 0;
}
