#include "PostProcessor.h"

PostProcessor::PostProcessor(Shader * shader, GLfloat width, GLfloat height):
	PostProcessingShader(shader),Width(width),Height(height)
{
	glGenFramebuffers(1, &MSFBO);
	glGenFramebuffers(1, &FBO);
	glGenRenderbuffers(1, &RBO);
	// MSFBO
	glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, Width, Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR:POSTPROCESSOR: Failed to initialize MSFBO");
	}
	//FBO
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	Texture = new Texture2D("InternalTexture");
	Texture->Generate(width, height, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture->GetId(), 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)!= GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR:POSTPROCESSOR:Failed to initialize FBO");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//VAO
	InitRenderData();

	GLfloat offset = 1.0f / 300.0f;
	GLfloat offsets[9][2] = {
		{ -offset,  offset  },  // top-left
		{  0.0f,    offset  },  // top-center
		{  offset,  offset  },  // top-right
		{ -offset,  0.0f    },  // center-left
		{  0.0f,    0.0f    },  // center-center
		{  offset,  0.0f    },  // center - right
		{ -offset, -offset  },  // bottom-left
		{  0.0f,   -offset  },  // bottom-center
		{  offset, -offset  }   // bottom-right    
	};
	GLint edge_kernel[9] = {
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};
	GLfloat blur_kernel[9] = {
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16
	};
	PostProcessingShader->Use();
	PostProcessingShader->SetUniform2fv("offsets", 9, (GLfloat*)offsets);
	PostProcessingShader->SetUniform1iv("edge_kernel", 9, edge_kernel);
	PostProcessingShader->SetUniform1fv("blur_kernel", 9, blur_kernel);

}
void PostProcessor::InitRenderData()
{
	//GLfloat vertices[] = {
	//	// Pos      // Tex
	//	0.f, 0.f, 0.0f, 0.0f,
	//	1.f, 1.f, 1.0f, 1.0f,
	//	0.0f, 1.f, 0.0f, 1.f,

	//	0.0f, 0.0f, 0.0f, 0.0f,
	//	1.0f, 0.f, 1.0f, 0.f,
	//	1.0f, 1.0f, 1.0f, 1.0f
	//};
	GLfloat vertices[] = {
		// Pos        // Tex
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};
	GLuint  VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT),(GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void PostProcessor::BeginRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void PostProcessor::EndRender()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
	glBlitFramebuffer(0, 0, Width, Height, 0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void PostProcessor::Render(GLfloat time)
{
	PostProcessingShader->Use();
	PostProcessingShader->SetUniform1f("time", time);
	PostProcessingShader->SetUniform1i("confuse", Confuse);
	PostProcessingShader->SetUniform1i("chaos", Chaos);
	PostProcessingShader->SetUniform1i("shake", Shake);

	glActiveTexture(GL_TEXTURE0);
	Texture->Bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
