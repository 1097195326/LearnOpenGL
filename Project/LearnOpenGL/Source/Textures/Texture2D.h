#pragma once

#include "Headle.h"




class Texture2D
{
private:
	GLuint ID, Width, Height;
	string	Name;
public:
	Texture2D(string textureName);
	virtual ~Texture2D();
	
	GLuint Internal_Format, Image_Format, Wrap_S, Wrap_T, Filter_Min, Filter_Max;


	void	Generate(GLuint width, GLuint height, unsigned char * data);
	void	Bind();

};