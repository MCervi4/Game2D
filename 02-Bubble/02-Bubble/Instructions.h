#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE


#include "Sprite.h"
#include "TexturedQuad.h"
#include "Button.h"


class Instructions
{
public:
	void init(ShaderProgram& shaderProgram);
	void render();


private:

	Texture texs[3];
	TexturedQuad* texQuad[3];
	Button returnbut;
};

#endif