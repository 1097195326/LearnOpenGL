#pragma once

#include "../Headle.h"
#include "../Managers/ResourceManager.h"
#include "GameLevel.h"


const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);


class Game
{
private:
	GLfloat	ScreenWidth, ScreenHeight;
	vector<GameLevel*>		Levels;
	GLuint					Level;

	GameObject *			Player;
public:
	GLboolean		Keys[1024];

	Game(GLfloat width, GLfloat height);
	virtual ~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

};