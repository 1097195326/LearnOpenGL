#pragma once



#include "Headle.h"
#include "Shader/Shader.h"

struct Character
{
	GLuint	TextureId;
	ivec2	Size;
	ivec2	Bearing;
	GLuint	Advance;
};
class TextRenderer
{
public:
	map<GLchar, Character>	Characters;
	Shader *	TextShader;
	TextRenderer(GLuint width, GLuint height);

	void Load(string font, GLuint fontSize);
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color = vec3(1.f));
private:
	GLuint VAO, VBO;
};