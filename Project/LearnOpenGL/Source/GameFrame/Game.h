#pragma once

#include "Headle.h"
#include "Managers/ResourceManager.h"
#include "GameLevel.h"
#include "Box2D/Box2D.h"
#include "BallObject.h"


const glm::vec2 PLAYER_SIZE(100, 20);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, 350.0f);
const GLfloat BALL_RADIUS = 12.5f;
const GLfloat PLAYER_VELOCITY(500.0f);

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game
{
private:
	GLfloat	ScreenWidth, ScreenHeight;
	vector<GameLevel*>		Levels;
	GLuint					Level;

	GameObject *			Player;
	BallObject *			Ball;
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


	void DoCollisions();
	// Reset
	void ResetLevel();
	void ResetPlayer();
};