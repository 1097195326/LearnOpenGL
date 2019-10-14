#pragma once


#include "../Headle.h"
#include "../Textures/Texture2D.h"
#include "../Sprite/Sprite.h"

class GameObject
{
public:
	vec2	Position, Size, Velocity;
	vec3	Color;
	GLfloat		Rotate;
	GLboolean	IsSolid;
	GLboolean	IsDestroyed;

	Texture2D *		Texture;

	GameObject();
	GameObject(Texture2D * texture, vec2 position, vec2 size, vec3 color = vec3(1.f), vec2 velocity = vec2(0.f));

	virtual void	Draw(Sprite * sprite);

};