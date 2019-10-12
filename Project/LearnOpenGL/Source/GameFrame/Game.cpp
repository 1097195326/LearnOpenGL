#include "Game.h"

Sprite * smileSprite = nullptr;

Game::Game(GLfloat width, GLfloat height)
{
	ScreenWidth = width;
	ScreenHeight = height;

}
Game::~Game()
{

}
void Game::Init()
{
	Shader * smileShader = RS_M->LoadShader("smile", "ShaderScript/VertexShader.txt", "ShaderScript/FragmentShader.txt");
	mat4   projection = ortho(0.f, ScreenWidth, ScreenHeight, 0.f, -1.f, 1.f);
	
	smileShader->Use();
	smileShader->SetUniform1i("image", 0);
	smileShader->SetUniformMatrix4fv("projection", projection);
	
	RS_M->LoadTexture2D("smile", "texture/awesomeface.png");

	smileSprite = new Sprite(smileShader);
}
void Game::ProcessInput(GLfloat dt)
{

}
void Game::Update(GLfloat dt)
{

}
void Game::Render()
{
	smileSprite->Draw(RS_M->GetTexture2D("smile"), vec2(200, 200), vec2(300, 400), 45.f, vec3(0.0f, 1.0f, 0.0f));


}