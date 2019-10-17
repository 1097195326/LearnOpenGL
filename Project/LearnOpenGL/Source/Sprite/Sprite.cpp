#include "Sprite.h"


Sprite::Sprite(Shader * temShader)
{
	UseShader = temShader;
	InitRenderData();
}
Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &SpriteVAO);
}
void Sprite::InitRenderData()
{
	GLuint VBO;
	//GLfloat vertices[] = {
	//	// Pos      // Tex
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 0.0f,

	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 0.0f
	//};
	GLfloat vertices[] = {
		// Pos      // Tex
		0.f, 0.f, 0.0f, 0.0f,
		1.f, 1.f, 1.0f, 1.0f,
		0.0f, 1.f, 0.0f, 1.f,

		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.f, 1.0f, 0.f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	glGenVertexArrays(1, &SpriteVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(SpriteVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void Sprite::Draw(Texture2D * texture, vec2 position, vec2 size /* = vec2(10, 10) */, GLfloat rotate /* = 0.f */, vec3 color /* = vec3(1) */)
{
	UseShader->Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	//model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	UseShader->SetUniformMatrix4fv("model", model);
	UseShader->SetUniform3fv("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	glBindVertexArray(SpriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}