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
	Texture texs[2];
	TexturedQuad* texQuad[2];
	Button start;
	Button howtoplay;
	Button levels;
	Button exit;
	//glm::mat4 projection;

};

#endif