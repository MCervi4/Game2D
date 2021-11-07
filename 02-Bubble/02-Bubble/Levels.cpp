#include "Levels.h"
#include "Game.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

void Levels::init(ShaderProgram& shaderProgram) {

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//BUTTONS
	un.init(shaderProgram, 130.f, 100.f, 205.f, 175.f, "images/1.png");
	dos.init(shaderProgram, 280.f, 100.f, 355.f, 175.f, "images/2.png");
	tres.init(shaderProgram, 430.f, 100.f, 505.f, 175.f, "images/3.png");
	quatre.init(shaderProgram, 205.f, 255.f, 280.f, 330.f, "images/4.png");
	cinc.init(shaderProgram, 355.f, 255.f, 430.f, 330.f, "images/5.png");
	returnbut.init(shaderProgram, 10.f, 440.f, 100.f, 470.f, "images/return.png");

}


void Levels::render() {
	texQuad->render(texs);
	un.render();
	dos.render();
	tres.render();
	quatre.render();
	cinc.render();
	returnbut.render();
}

int Levels::whereToGo(int x, int y)
{
	if (un.isPressed(x, y)) return 1;
	else if (dos.isPressed(x, y)) return 2;
	else if (tres.isPressed(x, y)) return 3;
	else if (quatre.isPressed(x, y)) return 4;
	else if (cinc.isPressed(x, y)) return 5;
	return 0;
}