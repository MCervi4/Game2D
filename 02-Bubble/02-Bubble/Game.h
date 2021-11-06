#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application

enum GameState {MENU, SCENE, INSTR, CRED};

class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	void initShaders();

private:

	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	Menu menu;
	
	GameState gamestate;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time

	//coses que abans estaven a scene
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
};


#endif // _GAME_INCLUDE


