#include "GameObject.h"
#include "Game.h"

GameObject::GameObject():
	Texture(nullptr), Position(vec2(0.f)),Size(vec2(1.f)),Velocity(vec2(0.f)),Color(vec3(1.f)),Rotate(0.f),IsDestroyed(false),IsSolid(false)
{

}
GameObject::GameObject(Texture2D * texture, vec2 position, vec2 size, vec3 color /* = vec3(1.f) */, vec2 velocity /* = vec2(0.f) */)
	:Texture(texture),Position(position),Size(size),Velocity(velocity),Color(color),IsSolid(false),IsDestroyed(false)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + size.x * 0.5f) * ToPhycisPer, (position.y + size.y * 0.5f) * ToPhycisPer);

	PhysicsBody = Game::Get()->PhysicsWorld->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(size.x * 0.5f * ToPhycisPer, size.y * 0.5f * ToPhycisPer);
	PhysicsBody->CreateFixture(&shape, 0.f);

}
void GameObject::Draw(Sprite * sprite)
{
	sprite->Draw(Texture, Position, Size, Rotate, Color);
}
void GameObject::Update(GLfloat dt)
{
	PhysicsBody->SetTransform(b2Vec2((Position.x + Size.x * 0.5f) * ToPhycisPer, (Position.y + Size.y * 0.5f) * ToPhycisPer), 0);
}