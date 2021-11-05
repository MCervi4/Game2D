#ifndef _BUTTON
#define _BUTTON


#include "Sprite.h"
#include "TexturedQuad.h"


class Button
{
public:
	void init(ShaderProgram& shaderProgram, int inix, int iniy,int fix,int fiy);
	void render();

	bool isPressed(int x, int y);

private:

	glm::vec2 geom[2];

	Texture texs;
	TexturedQuad* texQuad;


};

#endif#pragma once
