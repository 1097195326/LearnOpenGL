#pragma once

#include "Headle.h"

#include "GameObject.h"




class GameLevel
{
private:

	void		Init(const vector<vector<GLuint>> & tileData, GLfloat width, GLfloat height);

public:
	vector<GameObject * >	Bricks;

	void		Load(const GLchar * file, GLfloat width, GLfloat height);

	void		Draw(Sprite * sprite);

	GLboolean	IsComplete();

};