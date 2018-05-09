//
//  main.cpp
//  LearnOpenGL
//
//  Created by hongxing zhang on 2018/4/16.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GameHeader.h"

#include "ShaderProgram.h"
#include "FileHelper.h"
#include <GLFW/glfw3.h>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    
}
GLuint GetShaderProgram(const char * _VertexShaderSource, const char * _FragmentShaderSource)
{
    GLuint VertexShader,FragmentShader,ShaderProgram;
    // create vertex shader
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &_VertexShaderSource, NULL);
    glCompileShader(VertexShader);
    
    int Success;
    char InfoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
        printf("ERROR::SHADER::VERTEX::COMPILE_FAILED : %s",InfoLog);
    }
    // create fragment shader
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &_FragmentShaderSource, NULL);
    glCompileShader(FragmentShader);
    
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILE_FAILED : %s",InfoLog);
    }
    // create shader program
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);
    
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if(!Success)
    {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
        printf("ERROT::SHADER::PROGRAM::LINK_FAILED : %s",InfoLog);
    }
    // delete vertexShader, fragmentShader
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    
    return ShaderProgram;
}
int main(int argc, const char * argv[])
{
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
    glfwMakeContextCurrent(window);
    
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    GLuint VBO,EBO;
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    ShaderProgram * mShaderProgram = new ShaderProgram("Shaders/VertexShader.strings","Shaders/FragmentShader.strings");
    
    GLuint aPos;
    aPos = glGetAttribLocation(mShaderProgram->GetShaderProgramId(), "aPos");
    glEnableVertexAttribArray(aPos);
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
    
    while (!glfwWindowShouldClose(window))
    {
        // rendering
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mShaderProgram->UseShader();
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
