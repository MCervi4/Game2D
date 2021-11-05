#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "Sprite.h"
#include "TexturedQuad.h"
#include "Button.h"

//#include "SoundManager.h"

class Menu
{
public:
	void init(ShaderProgram& shaderProgram);
	void render();

private:
	//SoundManager sound;

	//Quad* quad;
	Texture texs[3];
	TexturedQuad* texQuad[10];
	Button boto;
	//glm::mat4 projection;

	/*bool introAnim;
	float backgroundPos;
	int cursor, inputDelay;
	Texture spritesheet, spritesheet2, spritesheet3;
	Sprite* background, * medal, * instructions;*/
};

#endif#pragma once
