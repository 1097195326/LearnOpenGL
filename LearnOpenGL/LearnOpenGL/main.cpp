//
//  main.cpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/4/16.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GameHeader.h"

#include "ShaderProgram.h"
#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "GActor.h"


glm::vec3 CameraPos(0,0,3);
glm::vec3 CameraFront(0,0,-1);
glm::vec3 CameraUp(0,1,0);

float LastFrame = 0.f;
float DeltaTime = 0.f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float CurrentFrame = glfwGetTime();
    DeltaTime = CurrentFrame - LastFrame;
    LastFrame = CurrentFrame;
    
    printf("DeltaTime : %f \n",DeltaTime);
    float CameraSpeed = 2.5f * DeltaTime;
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }else if(key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        CameraPos += CameraSpeed * CameraFront;
    }else if(key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        CameraPos -= CameraSpeed * CameraFront;
    }else if(key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
    }else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
    }//else if(key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        
    }
}
bool firstMouse = true;
float v_yaw   = -90.0f;
float v_pitch =  0.0f;
float lastX = 400.f;
float lastY = 300.f;
float fov = 45.f;

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
    
    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    v_yaw += xoffset;
    v_pitch += yoffset;
    
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (v_pitch > 89.0f)
        v_pitch = 89.0f;
    if (v_pitch < -89.0f)
        v_pitch = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(v_yaw)) * cos(glm::radians(v_pitch));
    front.y = sin(glm::radians(v_pitch));
    front.z = sin(glm::radians(v_yaw)) * cos(glm::radians(v_pitch));
    CameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
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
    GLFWwindow * window = glfwCreateWindow(800, 600, "HelloWindow", NULL, NULL);
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
    
    int screen_width,screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    GActor * actor = new GActor();
    actor->SetData(vertices,sizeof(vertices), 36);
    actor->SetTexture("Resource/Image/wall.jpg",0);
    actor->SetShader("Shaders/VertexShader.strings","Shaders/FragmentShader.strings");

    
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        // rendering
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(actor->GetShader());
        
        glm::mat4 model(1.f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.f), glm::vec3(0.5,1,0));
        glUniformMatrix4fv(glGetUniformLocation(actor->GetShader(), "model"), 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
        glUniformMatrix4fv(glGetUniformLocation(actor->GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)screen_width/(float)screen_height, 0.1f, 100.f);
        glUniformMatrix4fv(glGetUniformLocation(actor->GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        actor->Draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
