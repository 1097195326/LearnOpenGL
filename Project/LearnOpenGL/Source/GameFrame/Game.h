#pragma once

#include "../Headle.h"
#include "../Managers/ResourceManager.h"

class Game
{
private:
	GLfloat	ScreenWidth, ScreenHeight;

public:
	Game(GLfloat width, GLfloat height);
	virtual ~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

};