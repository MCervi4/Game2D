#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "Sprite.h"
//#include "SoundManager.h"

class Menu
{
public:
	void init(ShaderProgram& shaderProgram);
	void render();
	void update(int deltaTime);

private:
	//SoundManager sound;

	bool introAnim;
	float backgroundPos;
	int cursor, inputDelay;
	Texture spritesheet, spritesheet2, spritesheet3;
	Sprite* background, * medal, * instructions;
};

#endif