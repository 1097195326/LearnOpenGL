//
//  NewLoadModel.cpp
//  LearnOpenGL
//
//  Created by vv on 2019/1/10.
//  Copyright © 2019年 hongxing zhang. All rights reserved.
//

#include "StencilTest.hpp"

#include "../../glm/glm.hpp"
#include "../../ImageTool/stb_image.h"

#include "../../GameFrame/Camera/Camera.h"
#include "../../GameFrame/Camera/CameraManager.h"

#include "../../GameFrame/Render/ShaderProgram.h"
#include "Mesh.hpp"
#include "Model.hpp"
#include "../../GameFrame/Actor/GActor.h"


void StencilTest::Draw(GLFWwindow *window)
{
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    
    CameraManager::Get()->SetCamera(&camera);
    
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    GActor * actor = new GActor();
    actor->SetData(vertices,sizeof(vertices), 36);
    actor->SetShader("Shaders/lightmap/mvs.strings","Shaders/lightmap/mfs.strings",true ,false, true);
    //    actor->SetTexture("Resource/Image/container2.png",0,true);//Resource/cyborg/cyborg_specular.png
    actor->SetTexture("Resource/Image/container2.png",0,true);
    actor->SetTexture("Resource/Image/container2_specular.png",1,true);
    actor->SetPosition(vec3(0.f, 0.f, -3.f));
    actor->GetShader()->SetUniform3fv("ViewPos", camera.Position);
    actor->GetShader()->SetUniform3fv("light.position", lightPos);
    actor->GetShader()->SetUniform3fv("light.ambient", vec3(0.2f));
    actor->GetShader()->SetUniform3fv("light.diffuse", vec3(0.5f));
    actor->GetShader()->SetUniform3fv("light.specular", vec3(1.f));
    actor->GetShader()->SetUniform1i("material.diffuse", 0);
    actor->GetShader()->SetUniform1i("material.specular", 1);
    actor->GetShader()->SetUniform1f("material.shininess", 32.0f);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    ShaderProgram Singlehader("Shaders/lightmap/mvs.strings", "Shaders/StencilTest/stencil_single_color.fs");
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        mat4 model(1);
        model = glm::translate(model, glm::vec3(0.f, 0.f, -3.f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        
        actor->GetShader()->UseShader();
        actor->Draw();
        
        glStencilMask(0x00);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glDisable(GL_DEPTH_TEST);

        Singlehader.UseShader();
        Singlehader.SetUniformMatrix4fv("projection", projection);
        Singlehader.SetUniformMatrix4fv("view", view);
        Singlehader.SetUniformMatrix4fv("model", model);
        
        actor->Draw();
        
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
}
