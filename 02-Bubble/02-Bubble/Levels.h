#ifndef _LEVELS_INCLUDE
#define _LEVELS_INCLUDE


#include "Sprite.h"
#include "TexturedQuad.h"


class Levels
{
public:
	void init(ShaderProgram& shaderProgram);
	void render();


private:

	Texture texs;
	TexturedQuad* texQuad;

};

#endif