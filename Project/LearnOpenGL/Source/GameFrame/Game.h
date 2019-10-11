#pragma once

#include "../Headle.h"


class Game
{

public:
	Game(GLuint width,GLuint height);
	virtual ~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

};