//
//  NewLoadModel.cpp
//  LearnOpenGL
//
//  Created by vv on 2019/1/10.
//  Copyright © 2019年 hongxing zhang. All rights reserved.
//

#include "NewLoadModel.hpp"

#include "../../glm/glm.hpp"
#include "../../ImageTool/stb_image.h"

#include "../../GameFrame/Camera/Camera.h"
#include "../../GameFrame/Camera/CameraManager.h"

#include "../../GameFrame/Render/ShaderProgram.h"
#include "Mesh.hpp"
#include "Model.hpp"


void NewLoadModel::Draw(GLFWwindow *window)
{
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    CameraManager::Get()->SetCamera(&camera);
    
    Model * mmodel = new Model("Resource/cyborg/cyborg.obj");
    
    ShaderProgram ourShader("Shaders/LoadModel2.0/model_vs.strings", "Shaders/LoadModel2.0/model_fs.strings");
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.UseShader();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.SetUniformMatrix4fv("projection", projection);
        ourShader.SetUniformMatrix4fv("view", view);

        mat4 model(1);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.f));
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        ourShader.SetUniformMatrix4fv("model", model);
        
        mmodel->Draw(ourShader);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
}
