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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
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
        0.5f,  0.5f,    0.0f, 1.f,0.f,0.f,  1.f,1.f,// top right
        0.5f, -0.5f,    0.0f, 0.f,1.f,0.f,  1.f,0.f,// bottom right
        -0.5f, -0.5f,   0.0f,0.f,0.f,1.f,   0.f,0.f,// bottom left
        -0.5f,  0.5f,   0.0f,0.f,0.f,0.f,   0.f,1.f// top left
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
    
    // load image
    GLuint texture1,texture2;
    {
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        int image_width,image_height,image_nrchannel;
        unsigned char * data = stbi_load("Resource/Image/container.jpg", &image_width, &image_height, &image_nrchannel, 0);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(data);
    }
    {
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        int image_width,image_height,image_nrchannel;
        unsigned char * data = stbi_load("Resource/Image/wall.jpg", &image_width, &image_height, &image_nrchannel, 0);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(data);
    }
    
    
    // build shader
    ShaderProgram * mShaderProgram = new ShaderProgram("Shaders/VertexShader.strings","Shaders/FragmentShader.strings");
    
    GLuint aPos;
    aPos = glGetAttribLocation(mShaderProgram->GetShaderProgramId(), "aPos");
    glEnableVertexAttribArray(aPos);
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
    
    GLuint aColor;
    aColor = glGetAttribLocation(mShaderProgram->GetShaderProgramId(), "aColor");
    glEnableVertexAttribArray(aColor);
    glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    
    GLuint aCooPos;
    aCooPos = glGetAttribLocation(mShaderProgram->GetShaderProgramId(), "aCooPos");
    glEnableVertexAttribArray(aCooPos);
    glVertexAttribPointer(aCooPos, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    
    mShaderProgram->UseShader();
    
    glUniform1i(glGetUniformLocation(mShaderProgram->GetShaderProgramId(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(mShaderProgram->GetShaderProgramId(), "texture2"), 1);
    
    while (!glfwWindowShouldClose(window))
    {
        // rendering
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mShaderProgram->UseShader();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
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
