#include "GameObject.h"


GameObject::GameObject():
	Texture(nullptr), Position(vec2(0.f)),Size(vec2(1.f)),Velocity(vec2(0.f)),Color(vec3(1.f)),Rotate(0.f),IsDestroyed(false),IsSolid(false)
{

}
GameObject::GameObject(Texture2D * texture, vec2 position, vec2 size, vec3 color /* = vec3(1.f) */, vec2 velocity /* = vec2(0.f) */)
	:Texture(texture),Position(position),Size(size),Velocity(velocity),Color(color),IsSolid(false),IsDestroyed(false)
{

}
void GameObject::Draw(Sprite * sprite)
{
	sprite->Draw(Texture, Position, Size, Rotate, Color);
}