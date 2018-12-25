//
//  material.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/7/10.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "material.h"
#include "Camera.h"
#include "GActor.h"
#include "CameraManager.h"


void Material::Draw(GLFWwindow * window)
{
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
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
    actor->SetShader("Shaders/material/mvs.strings","Shaders/material/mfs.strings",true ,false, false);
    actor->SetPosition(vec3(0.f, 0.f, -3.f));
    actor->GetShader()->SetUniform3fv("ViewPos", camera.Position);
    actor->GetShader()->SetUniform3fv("light.position", lightPos);
    actor->GetShader()->SetUniform3fv("light.ambient", vec3(0.2f));
    actor->GetShader()->SetUniform3fv("light.diffuse", vec3(0.5f));
    actor->GetShader()->SetUniform3fv("light.specular", vec3(1.f));
    actor->GetShader()->SetUniform3fv("material.ambient", vec3(1.0f, 0.5f, 0.31f));
    actor->GetShader()->SetUniform3fv("material.diffuse", vec3(1.0f, 0.5f, 0.31f));
    actor->GetShader()->SetUniform3fv("material.specular", vec3(0.5f, 0.5f, 0.5f));
    actor->GetShader()->SetUniform1f("material.shininess", 32.0f);

    GActor * lightObject = new GActor();
    lightObject->SetData(vertices3,sizeof(vertices3), 36);
    lightObject->SetShader("Shaders/material/lvs.strings","Shaders/material/lfs.strings",true ,false, false);
    lightObject->SetPosition(lightPos);
    lightObject->GetShader()->SetUniform3fv("LightColor", vec3(1.f));

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
