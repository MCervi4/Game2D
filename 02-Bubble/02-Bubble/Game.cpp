#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	iniWidth = 0.f;
	finWidth = float(SCREEN_WIDTH - 1);
	finHeight = float(SCREEN_HEIGHT - 1);
	iniHeight = 0.f;

	initShaders();
	projection = glm::ortho(iniWidth, finWidth, finHeight, iniHeight);
	//projection = glm::ortho(0.f, float(max(SCREEN_WIDTH - 1), POSICIO JUGADOR 1), float(max(SCREEN_HEIGHT - 1), POSICIO JUGADOR 2), 0.f);
	//projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	gamestate = MENU;

	//scene.init(texProgram);
	menu.init(texProgram);
}

bool Game::update(int deltaTime)
{
	currentTime += deltaTime;

	if (gamestate == SCENE) {
		scene.update(deltaTime, iniWidth, finWidth, iniHeight, finHeight);
		float playersPosX = scene.getPlayersPosX();// +float(SCREEN_WIDTH) / 10.f;
		float playersPosY = scene.getPlayersPosY();// +float(SCREEN_HEIGHT) / 10.f;

		iniWidth = playersPosX - float(SCREEN_WIDTH) * 0.6f;
		finWidth = playersPosX + float(SCREEN_WIDTH) * 0.6f;

		iniHeight = playersPosY - float(SCREEN_HEIGHT) * 0.6f;
		finHeight = playersPosY + float(SCREEN_HEIGHT) * 0.6f;

		projection = glm::ortho(iniWidth, finWidth, finHeight, iniHeight);

		if (scene.getFinal() == true)
		{
			gamestate = CRED;
			credits.init(texProgram, true);
		}
	}
	else {
		iniWidth = 0.f;
		finWidth = float(SCREEN_WIDTH - 1);
		iniHeight = float(SCREEN_HEIGHT - 1);
		finHeight = 0.f;

		projection = glm::ortho(iniWidth, finWidth, iniHeight, finHeight);
	}
	
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
	else if (gamestate == SCENE) scene.render();
	else if (gamestate == INSTR) instr.render();
	else if (gamestate == LEVELS) levels.render();
	else if (gamestate == CRED) credits.render();
	
}


void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	if (gamestate == SCENE)
	{
		switch (key)
		{
		case '1':
			scene.init(texProgram, 1);

			break;

		case '2':
			scene.init(texProgram, 2);
			break;

		case '3':
			scene.init(texProgram, 3);
			break;

		case '4':
			scene.init(texProgram, 4);
			break;

		case '5':
			scene.init(texProgram, 5);
			break;

		case 'g':
			scene.switchGodmode();
			break;
		case 'm':
			//MUTEJAR MUSICA
			break;
		case 'b':
			gamestate = MENU;
			menu.init(texProgram);
			break;
		default:
			break;
		}
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
			case 0:	//menu
				break;
			case 1: //start
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			case 2: //howtoplay
				gamestate =	INSTR;
				instr.init(texProgram);
				break;
			case 3: //levels
				gamestate = LEVELS;
				levels.init(texProgram);
				break;
			case 4: //credits
				gamestate = CRED;
				credits.init(texProgram, false);
				break;
			case 5: //exit
				bPlay = false;
				break;
			default:
				break;
			}
		}
	}
	else if (gamestate == LEVELS)
	{
		if (button == 0)
		{
			int whereToGo = levels.whereToGo(x, y);
			switch (whereToGo)
			{
			case 0:
				break;
			case 1:
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			case 2:
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			case 3:
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			case 4:
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			case 5:
				gamestate = SCENE;
				scene.init(texProgram, whereToGo);
				break;
			case 6:
				gamestate = MENU;
				menu.init(texProgram);
				break;
			default:
				break;
			}
		}
	}
	
	if (returnPressed(x, y)) {
		gamestate = MENU;
		menu.init(texProgram);
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

bool Game::returnPressed(int x, int y) {
	return x >= 10 && x <= 100 && y >= 440 && y <= 470;
}





