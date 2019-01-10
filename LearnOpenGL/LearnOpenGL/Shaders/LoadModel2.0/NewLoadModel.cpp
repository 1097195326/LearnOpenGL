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


unsigned int TextureFromFile(string filename)
{   
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << std::endl;
        stbi_image_free(data);
    }
    
    return textureID;
}

void NewLoadModel::Draw(GLFWwindow *window)
{
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    CameraManager::Get()->SetCamera(&camera);
    
    ShaderProgram ourShader("Shaders/LoadModel2.0/model_vs.strings", "Shaders/LoadModel2.0/model_fs.strings");
    
    vector<Vertex> vertexVector;
    vector<Texture> textureVector;
    vector<unsigned int> indices;
    
    vertexVector.reserve(3);
    textureVector.reserve(1);
    indices.reserve(3);
    
    Vertex vertex1({0.5f, -0.5f, 0.0f}, {0.0f, 0.0f});
    Vertex vertex2({-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f});
    Vertex vertex3({0.0f,  0.5f, 0.0f}, {0.5f, 1.0f });
    
    vertexVector.push_back(vertex1);
    vertexVector.push_back(vertex2);
    vertexVector.push_back(vertex3);

    indices.insert(indices.end(), {0,1,2});
    
    glActiveTexture(GL_TEXTURE0);
    
    Texture texture;
    texture.id = TextureFromFile("Resource/Image/container.jpg");
    texture.type = "texture_diffuse";
    textureVector.push_back(texture);

    Mesh mesh(vertexVector,textureVector,indices);
    
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
        model = glm::translate(model, glm::vec3(0.0f, 0.f, 0.f));
        ourShader.SetUniformMatrix4fv("model", model);
        
        mesh.Draw(ourShader);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
}
