#include "Menu.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Menu::init(ShaderProgram& shaderProgram) {

	//BACKGROUND
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs[0].loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//TITLE
	geom[0].x = 170.f;
	geom[0].y = 30.f;
	geom[1].x = 450.f;
	geom[1].y = 110.f;
	//glm::vec2 geom[2] = { glm::vec2(30.f, 30.f), glm::vec2(150, 60) };

	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs[1].loadFromFile("images/aval.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//BUTTONS
	start.init(shaderProgram, 220.f, 220.f, 420.f, 280.f, "images/start.png");
	howtoplay.init(shaderProgram, 220.f, 300.f, 420.f, 360.f, "images/howtoplay.png");
	levels.init(shaderProgram, 220.f, 380.f, 420.f, 440.f, "images/levels.png");
	exit.init(shaderProgram, 20.f, 410.f, 70.f, 460.f, "images/exit.png");


	
}


void Menu::render() {
	texQuad[0]->render(texs[0]);
	texQuad[1]->render(texs[1]);
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
