#pragma once

#include "Headle.h"
#include "Managers/ResourceManager.h"
#include "GameLevel.h"
#include "Box2D/Box2D.h"


const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);


class Game
{
private:
	GLfloat	ScreenWidth, ScreenHeight;
	vector<GameLevel*>		Levels;
	GLuint					Level;

	GameObject *			Player;
public:
	GLboolean		Keys[1024];
	b2World *				PhysicsWorld;


	Game(GLfloat width, GLfloat height);
	virtual ~Game();

	static Game * Get();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

};