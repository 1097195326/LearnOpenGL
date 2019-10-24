#pragma once


#include "Headle.h"

#include "Shader/Shader.h"
#include "Textures/Texture2D.h"


class PostProcessor
{
public:
	Shader * PostProcessingShader;
	Texture2D * Texture;
	GLfloat	Width, Height;
	GLboolean	Confuse, Chaos, Shake;
	PostProcessor(Shader * shader, GLfloat width, GLfloat height);

	void	BeginRender();
	void	EndRender();
	void	Render(GLfloat time);
private:
	GLuint MSFBO, FBO, RBO, VAO;

	void	InitRenderData();
};