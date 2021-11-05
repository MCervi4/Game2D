#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Button.h"
#include <iostream>

void Button::init(ShaderProgram& shaderProgram, int inix, int iniy, int fix, int fiy)
{
	geom[0].x = inix;
	geom[0].y = iniy;
	geom[1].x = fix;
	geom[1].y = fiy;
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };


	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	texs.loadFromFile("images/button.png", TEXTURE_PIXEL_FORMAT_RGBA);
}
void Button::render()
{
	texQuad->render(texs);
}



bool Button::isPressed(int x, int y)
{
	return x >= geom[0].x && x <= geom[1].x && y >= geom[0].y && y <= geom[1].y;
}