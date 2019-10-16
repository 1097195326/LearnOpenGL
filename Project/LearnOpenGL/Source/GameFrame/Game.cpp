#include "Game.h"



Sprite * smileSprite = nullptr;
static Game * GameInstance = nullptr;

Game * Game::Get()
{
	return GameInstance;
}
Game::Game(GLfloat width, GLfloat height)
{
	GameInstance = this;

	ScreenWidth = width;
	ScreenHeight = height;

	PhysicsWorld = new b2World(b2Vec2(0, 0));

	b2BodyDef groundDef;
	groundDef.position.Set(width * 0.5f * ToPhycisPer, height * 0.5f * ToPhycisPer);
	b2Body * groundBody = PhysicsWorld->CreateBody(&groundDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(width * 0.5f * ToPhycisPer, height * 0.5f * ToPhycisPer);
	groundBody->CreateFixture(&groundBox,0.f);

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
	
	smileSprite = new Sprite(smileShader);

	RS_M->LoadTexture2D("smile", "texture/awesomeface.png");
	RS_M->LoadTexture2D("background", "texture/background.jpg");
	RS_M->LoadTexture2D("block", "texture/block.png");
	RS_M->LoadTexture2D("block_solid", "texture/block_solid.png");
	RS_M->LoadTexture2D("paddle", "texture/paddle.png");


	vec2 playerPos = glm::vec2(ScreenWidth / 2 - PLAYER_SIZE.x / 2, ScreenHeight - PLAYER_SIZE.y);
	Player = new GameObject(RS_M->GetTexture2D("paddle"), playerPos, PLAYER_SIZE);

	GameLevel * one = new GameLevel();
	one->Load("levels/lvlone.txt", ScreenWidth, ScreenHeight * 0.5f);
	GameLevel * two = new GameLevel();
	two->Load("levels/lvltwo.txt", ScreenWidth, ScreenHeight * 0.5f);
	GameLevel * three = new GameLevel();
	three->Load("levels/lvlthree.txt", ScreenWidth, ScreenHeight * 0.5f);
	GameLevel * four = new GameLevel();
	four->Load("levels/lvlfour.txt", ScreenWidth, ScreenHeight * 0.5f);

	Levels.push_back(one);
	Levels.push_back(two);
	Levels.push_back(three);
	Levels.push_back(four);

	Level = 0;

}
void Game::ProcessInput(GLfloat dt)
{
	GLfloat velocity = PLAYER_VELOCITY * dt;
	
	if (this->Keys[GLFW_KEY_A])
	{
		if (Player->Position.x >= 0)
			Player->Position.x -= velocity;
		if (Player->Position.x < 0)
		{
			Player->Position.x = 0.f;
		}
	}
	if (this->Keys[GLFW_KEY_D])
	{
		if (Player->Position.x <= ScreenWidth - Player->Size.x)
			Player->Position.x += velocity;
		if (Player->Position.x > ScreenWidth - Player->Size.x)
		{
			Player->Position.x = ScreenWidth - Player->Size.x;
			
		}
	}
}
void Game::Update(GLfloat dt)
{

	Player->Update(dt);

}
void Game::Render()
{
	smileSprite->Draw(RS_M->GetTexture2D("background"), vec2(0.f), vec2(ScreenWidth, ScreenHeight));

	Levels[Level]->Draw(smileSprite);

	Player->Draw(smileSprite);
}