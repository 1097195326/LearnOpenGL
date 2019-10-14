#pragma once

#include "../Headle.h"

#include "GameObject.h"




class GameLevel
{
private:
	vector<GameObject * >	Bricks;

	void		Init(const vector<vector<GLuint>> & tileData, GLfloat width, GLfloat height);

public:
	
	void		Load(const GLchar * file, GLfloat width, GLfloat height);

	void		Draw(Sprite * sprite);

	GLboolean	IsComplete();

};