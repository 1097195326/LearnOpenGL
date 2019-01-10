////
////  LoadModel.c
////  LearnOpenGL
////
////  Created by hongxing zhang on 2018/10/3.
////  Copyright © 2018年 hongxing zhang. All rights reserved.
////
//
//#include "LoadModel.h"
//#include "../../glm/glm.hpp"
//#include "../../GameFrame/Actor/mesh.h"
//#include "../../GameFrame/Actor/model.h"
//#include "Camera.h"
//#include "CameraManager.h"
//
//void LoadModel::Draw(GLFWwindow *window)
//{
//    glm::vec3 light_Pos(1.2f, 1.0f, 2.0f);
//    // camera
//    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//    
//    CameraManager::Get()->SetCamera(&camera);
//    
//    glEnable(GL_DEPTH_TEST);
//    
//    ShaderProgram ourShader("Shaders/loadmodel/model_vs.strings", "Shaders/loadmodel/model_fs.strings");
//    
//    Model ourModel("Resource/cyborg/cyborg.obj");
//    
//    while (!glfwWindowShouldClose(window))
//    {
//        // rendering
//        glClearColor(0.f, 0.5f, 0.f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        ourShader.UseShader();
//        
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        ourShader.SetUniformMatrix4fv("projection", projection);
//        ourShader.SetUniformMatrix4fv("view", view);
//
//        // render the loaded model
//        glm::mat4 model(1);
//        model = glm::translate(model, glm::vec3(0.0f, 0.f, -3.f)); // translate it down so it's at the center of the scene
////        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
//        ourShader.SetUniformMatrix4fv("model", model);
//        ourModel.Draw(ourShader);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//}
