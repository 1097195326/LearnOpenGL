
#include "Headle.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Managers/ResourceManager.h"
#include "GameFrame/Game.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);*/
	
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Game  BreakOut(SCR_WIDTH,SCR_HEIGHT);
	BreakOut.Init();

	GLfloat		DeltaTime = 0.f;
	GLfloat		LastFrame = 0.f;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		GLfloat	CurrentFrame = glfwGetTime();
		DeltaTime = CurrentFrame - LastFrame;
		LastFrame = CurrentFrame;

		BreakOut.ProcessInput(DeltaTime);

		BreakOut.Update(DeltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		BreakOut.Render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}