#ifndef _LEVELS_INCLUDE
#define _LEVELS_INCLUDE


#include "Sprite.h"
#include "TexturedQuad.h"
#include "Button.h"


class Levels
{
public:
	void init(ShaderProgram& shaderProgram);
	void render();
	int whereToGo(int x, int y);


private:

	Texture texs;
	TexturedQuad* texQuad;

	Button un;
	Button dos;
	Button tres;
	Button quatre;
	Button cinc;
	Button returnbut;

};

#endif