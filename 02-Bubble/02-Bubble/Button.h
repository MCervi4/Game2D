#ifndef _BUTTON
#define _BUTTON


#include "Sprite.h"
#include "TexturedQuad.h"


class Button
{
public:
	// int inix, int iniy, int fix, int fiy
	// geom[0].x, geom[0].y, geom[1].x, geom[1].y
	void init(ShaderProgram& shaderProgram, float inix, float iniy, float fix, float fiy);
	void render();

	bool isPressed(int x, int y);

private:


	glm::vec2 geom[2];

	Texture texs;
	TexturedQuad* texQuad;


};

#endif
