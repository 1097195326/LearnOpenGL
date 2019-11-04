#include "Game.h"
#include "PostProcessor.h"
#include "TextRenderer.h"

Sprite * smileSprite = nullptr;
PostProcessor * postProcessor = nullptr;
TextRenderer * textRenderer = nullptr;
static Game * GameInstance = nullptr;

GLfloat	ShakeTime = 0.f;

Game * Game::Get()
{
	return GameInstance;
}
Game::Game(GLfloat width, GLfloat height)
{
	GameInstance = this;

	ScreenWidth = width;
	ScreenHeight = height;

	/*PhysicsWorld = new b2World(b2Vec2(0, 0));

	b2BodyDef groundDef;
	groundDef.position.Set(width * 0.5f * ToPhycisPer, height * 0.5f * ToPhycisPer);
	b2Body * groundBody = PhysicsWorld->CreateBody(&groundDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(width * 0.5f * ToPhycisPer, height * 0.5f * ToPhycisPer);
	groundBody->CreateFixture(&groundBox,0.f);*/

}
Game::~Game()
{

}
void Game::Init()
{
	textRenderer = new TextRenderer(ScreenWidth, ScreenHeight);
	textRenderer->Load("fonts/bttf.ttf", 24);

	Shader * smileShader = RS_M->LoadShader("smile", "ShaderScript/VertexShader.txt", "ShaderScript/FragmentShader.txt");
	//mat4   projection = ortho(0.f, ScreenWidth, ScreenHeight, 0.f, -1.f, 1.f);
	//mat4   projection = ortho(-ScreenWidth * 0.5f, ScreenWidth* 0.5f, -ScreenHeight * 0.5f, ScreenHeight* 0.5f, -10.f, 10.f);
	mat4   projection = ortho(0.f, ScreenWidth, 0.f, ScreenHeight, -10.f, 10.f);
	
	smileShader->Use();
	smileShader->SetUniform1i("image", 0);
	smileShader->SetUniformMatrix4fv("projection", projection);
	
	smileSprite = new Sprite(smileShader);

	Shader * postShader = RS_M->LoadShader("postShader", "ShaderScript/PostProcessV.txt", "ShaderScript/PostProcessF.txt");

	postProcessor = new PostProcessor(postShader, ScreenWidth, ScreenHeight);
	//postProcessor->Shake = GL_TRUE;
	//postProcessor->Confuse = GL_TRUE;
	//postProcessor->Chaos = GL_TRUE;

	RS_M->LoadTexture2D("smile", "texture/awesomeface.png");
	RS_M->LoadTexture2D("background", "texture/background.jpg");
	RS_M->LoadTexture2D("block", "texture/block.png");
	RS_M->LoadTexture2D("block_solid", "texture/block_solid.png");
	RS_M->LoadTexture2D("paddle", "texture/paddle.png");


	vec2 playerPos = glm::vec2(ScreenWidth / 2 - PLAYER_SIZE.x / 2, 0.f);
	Player = new GameObject(RS_M->GetTexture2D("paddle"), playerPos, PLAYER_SIZE);

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, PLAYER_SIZE.y);
	Ball = new BallObject(RS_M->GetTexture2D("smile"), ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY);


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
		if (Ball->Stuck)
			Ball->Position.x = Player->Position.x + PLAYER_SIZE.x * 0.5f - BALL_RADIUS;
	}
	if (this->Keys[GLFW_KEY_D])
	{
		if (Player->Position.x <= ScreenWidth - Player->Size.x)
			Player->Position.x += velocity;
		if (Player->Position.x > ScreenWidth - Player->Size.x)
		{
			Player->Position.x = ScreenWidth - Player->Size.x;
		}
		if (Ball->Stuck)
			Ball->Position.x = Player->Position.x + PLAYER_SIZE.x * 0.5f - BALL_RADIUS;
	}
	if (Keys[GLFW_KEY_SPACE])
	{
		Ball->Stuck = false;
	}
}
void Game::Update(GLfloat dt)
{
	Ball->Move(dt, ScreenWidth, ScreenHeight);
	Player->Update(dt);
	DoCollisions();

	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			postProcessor->Shake = GL_FALSE;
	}

	if (Ball->Position.y <= 0) // Did ball reach bottom edge?
	{
		this->ResetLevel();
		this->ResetPlayer();
	}
}
void Game::Render()
{
	postProcessor->BeginRender();

	smileSprite->Draw(RS_M->GetTexture2D("background"), vec2(0.f), vec2(ScreenWidth , ScreenHeight));
	Levels[Level]->Draw(smileSprite);
	Ball->Draw(smileSprite);
	Player->Draw(smileSprite);

	postProcessor->EndRender();
	postProcessor->Render(glfwGetTime());

	//textRenderer->RenderText("level1", ScreenWidth * 0.5f, ScreenHeight * 0.5f, 1.f);
	textRenderer->RenderText("zhang hong xing", 0.f, 0.f, 1.f);
}

//--------------------

void Game::ResetLevel()
{
	if (Level == 0)
	{
		Levels[Level]->Load("levels/lvlone.txt", ScreenWidth, ScreenHeight * 0.5f);
	}else if (Level == 1)
	{
		Levels[Level]->Load("levels/lvltwo.txt", ScreenWidth, ScreenHeight * 0.5f);
	}
	else if (Level == 2)
	{
		Levels[Level]->Load("levels/lvlthree.txt", ScreenWidth, ScreenHeight * 0.5f);
	}
	else if (Level == 3)
	{
		Levels[Level]->Load("levels/lvlfour.txt", ScreenWidth, ScreenHeight * 0.5f);
	}
}

void Game::ResetPlayer()
{
	// Reset player/ball stats
	vec2 playerPos = glm::vec2(ScreenWidth / 2 - PLAYER_SIZE.x / 2, 0.f);

	Player->Size = PLAYER_SIZE;
	Player->Position = playerPos;
	Ball->Reset(playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, PLAYER_SIZE.y), INITIAL_BALL_VELOCITY);
}



// Collision detection
GLboolean CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
	for (GameObject * box : Levels[Level]->Bricks)
	{
		if (!box->IsDestroyed)
		{
			Collision collision = CheckCollision(*Ball, *box);
			if (std::get<0>(collision)) // If collision is true
			{
				// Destroy block if not solid
				if (!box->IsSolid)
					box->IsDestroyed = GL_TRUE;
				else
				{
					ShakeTime = 0.05f;
					postProcessor->Shake = GL_TRUE;
				}
				// Collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // Horizontal collision
				{
					Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
					// Relocate
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration; // Move ball to right
					else
						Ball->Position.x -= penetration; // Move ball to left;
				}
				else // Vertical collision
				{
					Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
					// Relocate
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
						Ball->Position.y -= penetration; // Move ball bback up
					else
						Ball->Position.y += penetration; // Move ball back down
				}
			}
		}
	}
	// Also check collisions for player pad (unless stuck)
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		// Check where it hit the board, and change velocity based on where it hit the board
		GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
		GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		GLfloat percentage = distance / (Player->Size.x / 2);
		// Then move accordingly
		GLfloat strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		//Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
		// Fix sticky paddle
		Ball->Velocity.y = abs(Ball->Velocity.y);
	}
}

GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
	// Get center point circle first 
	glm::vec2 center(one.Position + one.Radius);
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// Now retrieve vector between center circle and closest point AABB and check if length < radius
	difference = closest - center;

	if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

// Calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}