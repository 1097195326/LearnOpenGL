#pragma once
#include "GameObject.h"


class BallObject : public GameObject
{
public:
	
	GLfloat   Radius;
	GLboolean Stuck;
	
	BallObject();
	BallObject(Texture2D * texture, vec2 pos, GLfloat radius, glm::vec2 velocity);
	
	vec2 Move(GLfloat dt, GLfloat window_width, GLfloat window_height);
	
	void      Reset(vec2 position, vec2 velocity);
};