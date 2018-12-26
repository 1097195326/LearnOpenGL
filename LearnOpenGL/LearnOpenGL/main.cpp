//
//  main.cpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/4/16.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GameHeader.h"
#include "Glad/glad.h"
#include "ImageTool/stb_image.h"
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
#include "CameraManager.h"
#include "material.h"
#include "lightmap.h"
#include "LoadModel.h"

#include <string>



float LastFrame = 0.f;
float DeltaTime = 0.f;

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
//    vector<int> ss = {1,4,5,9,2,6};
//
//    srand((unsigned)time(NULL));
//    sort(ss.begin(), ss.end());
//    random_shuffle(ss.begin(), ss.end());
    
//    ReceiveMsg * r = new ReceiveMsg();
//    SendMsg * s = new SendMsg();
//    s->Send();
//    delete r;
//    delete s;
//    return 0;
    
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
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, &key_callback);
    glfwSetCursorPosCallback(window, &mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    int screen_width,screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

//    while (!glfwWindowShouldClose(window))
//    {
//        // rendering
//        glClearColor(0.0, 0.5, 0.5, 1.0);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    unsigned int VAO;
//    glGenVertexArrays(1,&VAO);
//    glBindVertexArray(VAO);

    //--- draw ---
//    Material::Draw(window);
//    LightMap::Draw(window);
    LoadModel::Draw(window);
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
