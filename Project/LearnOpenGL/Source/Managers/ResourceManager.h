#pragma once


#include "../Headle.h"
#include "../Shader/Shader.h"
#include "../Textures/Texture2D.h"
#include "../Sprite/Sprite.h"


#include <map>


class  ResourceManager
{
private:
	map<string, Shader*>		Shaders;
	map<string, Texture2D*>		Textures;

public:
	static ResourceManager * Get();

	Shader *	LoadShader(string shaderName, const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile = nullptr);
	Shader *	GetShader(string shaderName);
	bool		RemoveShader(string shaderName);

	Texture2D * LoadTexture2D(string textureName, const GLchar * file);
	Texture2D * GetTexture2D(string textureName);
	bool		RemoveTexture2D(string textureName);

	void		Clear();
};

#define  RS_M ResourceManager::Get()