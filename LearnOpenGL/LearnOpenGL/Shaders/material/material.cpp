//
//  material.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/7/10.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "material.hpp"
#include "Camera.h"
#include "GActor.h"
#include "CameraManager.h"

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void Material::Draw(GLFWwindow * window)
{
    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    
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
}
