#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

class Application
{
public:
	void Run()
	{
		InitWindow();
		InitVulkan();
		MainLoop();
		CleanUp();
	}
private:
	void MainLoop()
	{
		while (!glfwWindowShouldClose(Window))
		{
			glfwPollEvents();
		}
	}
	void InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		Window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

	}
	void InitVulkan()
	{
		CreateInstance();
	}
	void CreateInstance()
	{
		VkApplicationInfo AppInfo = {};
		AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		AppInfo.pNext = nullptr;
		AppInfo.pApplicationName = "Game";
		AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		AppInfo.pEngineName = "No Engine";
		AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		AppInfo.apiVersion = VK_API_VERSION_1_2;

		VkInstanceCreateInfo CreateInfo = {};
		CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		//CreateInfo.pNext = nullptr;
		CreateInfo.pApplicationInfo = &AppInfo;

		unsigned int glfwExtensionCount = 0;
		const char ** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		CreateInfo.enabledExtensionCount = glfwExtensionCount;
		CreateInfo.ppEnabledExtensionNames = glfwExtensions;
		CreateInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&CreateInfo,nullptr,&Instance) != VK_SUCCESS)
		{
			std::printf("zhx:vkCreateInstance fail");
		}
	}
	void CleanUp()
	{
		vkDestroyInstance(Instance, nullptr);
		glfwDestroyWindow(Window);
		glfwTerminate();
	}

	VkInstance Instance;
	GLFWwindow * Window;

};
int main() {
	
	Application App;
	App.Run();

	return 0;
}