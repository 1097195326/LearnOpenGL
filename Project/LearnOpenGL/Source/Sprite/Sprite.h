#pragma once


#include "Headle.h"
#include "Shader/Shader.h"
#include "Textures/Texture2D.h"

class Sprite
{
private:
	Shader	*	UseShader;
	GLuint		SpriteVAO;

	void		InitRenderData();
public:
	Sprite(Shader * temShader);
	virtual ~Sprite();

	void Draw(Texture2D * texture, vec2 position, vec2 size = vec2(10, 10), GLfloat rotate = 0.f, vec3 color = vec3(1));

};