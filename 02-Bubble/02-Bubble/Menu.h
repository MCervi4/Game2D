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

	//funcio que segons el boto que apretes et diu on anar
	int whereToGo(int x, int y);

private:

	//SoundManager sound;
	//Quad* quad;
	Texture texs;
	TexturedQuad* texQuad;
	Button start;
	Button howtoplay;
	Button levels;
	Button credits;
	Button exit;
	//glm::mat4 projection;
};

#endif