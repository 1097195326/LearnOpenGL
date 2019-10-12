#include "ResourceManager.h"
#include "../Tools/FileHelper.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

ResourceManager * ResourceManager::Get()
{
	static ResourceManager rsm;
	return &rsm;
}
Shader * ResourceManager::LoadShader(string shaderName, const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile /* = nullptr */)
{
	string vertexShaderSource = FileHelper::ReadFileToString(vShaderFile);
	string fragmentShaderSource = FileHelper::ReadFileToString(fShaderFile);

	Shader * shader = new Shader(shaderName);
	if (shader->Generate(vertexShaderSource, fragmentShaderSource))
	{
		Shaders.insert(std::pair<string, Shader*>(shaderName, shader));
		return shader;
	}
	delete shader;
	return nullptr;
}
Shader * ResourceManager::GetShader(string shaderName)
{
	if (Shaders.find(shaderName) != Shaders.end())
	{
		return Shaders[shaderName];
	}
	return nullptr;
}
bool ResourceManager::RemoveShader(string shaderName)
{
	if (Shaders.find(shaderName) != Shaders.end())
	{
		delete Shaders[shaderName];
		Shaders.erase(shaderName);
		return true;
	}
	return false;
}
Texture2D * ResourceManager::LoadTexture2D(string textureName, const GLchar * file)
{
	int i_width, i_hight, image_chancel;
	unsigned char * data = stbi_load(file, &i_width, &i_hight, &image_chancel, 0);
	
	if (data)
	{
		Texture2D * texture = new Texture2D(textureName);
		if (image_chancel == 4)
		{
			texture->Internal_Format = GL_RGBA;
			texture->Image_Format = GL_RGBA;
		}
		texture->Generate(i_width, i_hight, data);
		Textures.insert(pair<string, Texture2D*>(textureName, texture));
		stbi_image_free(data);
		
		return texture;
	}
	return nullptr;
}
Texture2D * ResourceManager::GetTexture2D(string textureName)
{
	if (Textures.find(textureName) != Textures.end())
	{
		return Textures[textureName];
	}
	return nullptr;
}
bool ResourceManager::RemoveTexture2D(string textureName)
{
	if (Textures.find(textureName) != Textures.end())
	{
		delete Textures[textureName];
		Textures.erase(textureName);
		return true;
	}
	return false;
}
void ResourceManager::Clear()
{
	for (auto temShader : Shaders)
	{
		delete temShader.second;
	}
	Shaders.clear();
	for (auto temTexture : Textures)
	{
		delete temTexture.second;
	}
	Textures.clear();
}