#include "BallObject.h"



BallObject::BallObject()
	: GameObject(), Radius(12.5f), Stuck(true) { }

BallObject::BallObject(Texture2D * texture,vec2 pos, GLfloat radius, glm::vec2 velocity)
	: GameObject(texture,pos, vec2(radius * 2, radius * 2), glm::vec3(1.0f), velocity), Radius(radius), Stuck(true)
{

}

vec2 BallObject::Move(GLfloat dt, GLfloat window_width, GLfloat window_height)
{
	if (!Stuck)
	{
		Position += Velocity * dt;
		if (Position.x <= 0.0f)
		{
			Velocity.x = -Velocity.x;
			Position.x = 0.0f;
		}
		else if (Position.x + Size.x >= window_width)
		{
			Velocity.x = -Velocity.x;
			Position.x = window_width - Size.x;
		}
		if (Position.y <= 0.0f)
		{
			Velocity.y = -Velocity.y;
			Position.y = 0.0f;
		}else if (Position.y >= window_height - Size.y)
		{
			Velocity.y = -Velocity.y;
			Position.y = window_height - Size.y;
		}
	}
	return Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	Position = position;
	Velocity = velocity;
	Stuck = true;
}