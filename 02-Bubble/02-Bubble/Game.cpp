#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	gamestate = MENU;

	//scene.init(texProgram);
	menu.init(texProgram);
}

bool Game::update(int deltaTime)
{
	currentTime += deltaTime;

	if (gamestate == SCENE) scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (gamestate == MENU) menu.render();
	if (gamestate == SCENE) scene.render();
	
}

void Game::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;

	switch (key)
	{
	case '1':
		gamestate = SCENE;
		scene.init(texProgram, 1);
		break;

	case '2':
		gamestate = SCENE;
		scene.init(texProgram, 2);
		break;

	case '3':
		gamestate = SCENE;
		scene.init(texProgram, 3);
		break;

	case '4':
		gamestate = SCENE;
		scene.init(texProgram, 4);
		break;

	case '5':
		gamestate = SCENE;
		scene.init(texProgram, 5);
		break;

	case 'g':
		scene.switchGodmode();
		break;
	}



	keys[key] = true;

}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button, int x, int y)
{
	if (gamestate == MENU)
	{
		if (button == 0)
		{
			int whereToGo = menu.whereToGo(x, y);
			switch (whereToGo)
			{
			case 1:
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			}
		}
	}
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}







