#include "ResourceManager.h"


ResourceManager * ResourceManager::Get()
{
	static ResourceManager rsm;
	return &rsm;
}
Shader * ResourceManager::LoadShader(string shaderName, const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile /* = nullptr */)
{
	
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
		return true;
	}
	return false;
}
Texture2D * ResourceManager::LoadTexture2D(string textureName, const GLchar * file, GLboolean alpha)
{

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
	for (auto temTexture : Textures)
	{
		delete temTexture.second;
	}
}