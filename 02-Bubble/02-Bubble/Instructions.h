#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE


#include "Sprite.h"
#include "TexturedQuad.h"


class Instructions
{
public:
	void init(ShaderProgram& shaderProgram);
	void render();


private:

	Texture texs;
	TexturedQuad* texQuad;

};

#endif