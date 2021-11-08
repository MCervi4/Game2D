#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE


#include "Sprite.h"
#include "TexturedQuad.h"
#include "Button.h"


class Credits
{
public:
	void init(ShaderProgram& shaderProgram, bool final1);
	void render();

private:

	Texture texs;
	TexturedQuad* texQuad;

	Button returnbut;

	bool isFinal;

};

#endif