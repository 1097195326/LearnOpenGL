//
//  main.cpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/4/16.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GameHeader.h"

#include "Glad/glad.h"
//#include "GameHeader.h"

#include "ShaderProgram.h"
#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "GActor.h"
#include "CameraManager.h"

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

float LastFrame = 0.f;
float DeltaTime = 0.f;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float CurrentFrame = glfwGetTime();
    DeltaTime = CurrentFrame - LastFrame;
    LastFrame = CurrentFrame;
    
    printf("DeltaTime : %f \n",DeltaTime);
    float CameraSpeed = 2.5f * 0.2;
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CameraManager::Get()->GetCamera()->ProcessKeyboard(FORWARD, CameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CameraManager::Get()->GetCamera()->ProcessKeyboard(BACKWARD, CameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CameraManager::Get()->GetCamera()->ProcessKeyboard(LEFT, CameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CameraManager::Get()->GetCamera()->ProcessKeyboard(RIGHT, CameraSpeed);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    
    CameraManager::Get()->GetCamera()->ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    CameraManager::Get()->GetCamera()->ProcessMouseScroll(yoffset);
}


int main(int argc, const char * argv[])
{
    
//    return 0;
    // ----
    
    if(!glfwInit())
    {
        printf("glfw init fail \n");
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloWindow", NULL, NULL);
    if (window == NULL)
    {
        printf("windown is null \n");
        glfwTerminate();
    }
    glfwSetKeyCallback(window, &key_callback);
    glfwSetCursorPosCallback(window, &mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    int screen_width,screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);
    
    float vertices3[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    CameraManager::Get()->SetCamera(&camera);
    
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
//
    
    GActor * actor = new GActor();
    actor->SetData(vertices3,sizeof(vertices3), 36);
    actor->SetShader("Shaders/LightingObjectVertex.strings","Shaders/LightingObjectFrag.strings",true ,false, false);
    actor->SetPosition(vec3(0.f, 0.f, 0.f));
    actor->SetColor(vec3(1.0f, 0.5f, 0.31f));
    actor->SetLightColor(1.f);
    actor->SetLightPosition(lightPos);
//    actor->SetTexture("Resource/Image/wall.jpg",0);
//    actor->SetTexture("Resource/Image/container.jpg",1);
    
    
    GActor * lightObject = new GActor();
    lightObject->SetData(vertices3,sizeof(vertices3), 36);
    lightObject->SetShader("Shaders/LightVertex.strings","Shaders/LightFrag.strings",true ,false, false);
    lightObject->SetPosition(lightPos);
    lightObject->SetLightPosition(lightPos);
    lightObject->SetLightColor(1.f);
    lightObject->SetTexture("Resource/Image/container.jpg",0);
    
    
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        // rendering
        glClearColor(0.0, 0.5, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        actor->Draw();
        lightObject->Draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
