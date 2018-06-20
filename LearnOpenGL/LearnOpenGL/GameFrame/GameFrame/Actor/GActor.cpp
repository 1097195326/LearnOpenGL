//
//  GActor.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GActor.h"
#include "ShaderProgram.h"
#include "CameraManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GActor::GActor()
{
    m_Position = vec3(0);
    m_Scale = vec3(1.f);
}
GActor::~GActor()
{
    delete m_ShaderProgram;
    glDeleteBuffers(1, &m_VBO);
}
void GActor::SetData(float vertex[],int size, int count)
{
    m_VertexCount = count;
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}
void GActor::SetShader(std::string _vertexShader, std::string _fragmentShader,bool _haveNormal, bool _haveColor, bool _haveTexture)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    m_ShaderProgram = new ShaderProgram(_vertexShader.c_str(),_fragmentShader.c_str());
    
    m_ShaderProgram->UseShader();
    
    int strip = 3;
    int offset = 0;
    
    if (_haveNormal)
    {
        strip += 3;
    }
    if (_haveColor)
    {
        strip += 3;
    }
    if (_haveTexture)
    {
        strip += 2;
    }
    
    m_ShaderProgram->SetVertexAttribPointer("ObjectPosition", 3, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLAT), (GLvoid*)0);
    if (_haveNormal)
    {
        offset += 3;
        m_ShaderProgram->SetVertexAttribPointer("ObjectNormal", 3, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLAT), (GLvoid*)(offset * sizeof(GL_FLOAT)));
    }
    if (_haveColor)
    {
        offset += 3;
        m_ShaderProgram->SetVertexAttribPointer("ObjectColor", 3, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLAT), (GLvoid*)(offset * sizeof(GL_FLOAT)));
    }
    if(_haveTexture)
    {
        offset += 3;
        m_ShaderProgram->SetVertexAttribPointer("ObjectUVPos", 2, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLAT), (GLvoid*)(offset * sizeof(GL_FLOAT)));
        
//        glUniform1i(glGetUniformLocation(m_ShaderProgram->GetShaderProgramId(), "texture1"), 0);
//        glUniform1i(glGetUniformLocation(m_ShaderProgram->GetShaderProgramId(), "texture2"), 1);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void GActor::SetTexture(std::string imagePath, int index)
{
    
    switch (index) {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            glGenTextures(1, &m_Texture_0);
            glBindTexture(GL_TEXTURE_2D, m_Texture_0);
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            glGenTextures(1, &m_Texture_1);
            glBindTexture(GL_TEXTURE_2D, m_Texture_1);
            break;
        case 2:
            glGenTextures(1, &m_Texture_2);
            glBindTexture(GL_TEXTURE_2D, m_Texture_2);
            break;
        case 3:
            glGenTextures(1, &m_Texture_3);
            glBindTexture(GL_TEXTURE_2D, m_Texture_3);
            break;
        default:
            break;
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    int i_width,i_hight,image_chancel;
    unsigned char * data = stbi_load(imagePath.c_str(), &i_width, &i_hight, &image_chancel, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i_width, i_hight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
}
void GActor::SetPosition(vec3 pos)
{
    m_Position = pos;
}
vec3 GActor::GetPosition()
{
    return m_Position;
}
mat4 GActor::GetModelMat()
{
    mat4 model(1);
    model = glm::translate(model, m_Position);
    model = glm::scale(model, vec3(m_Scale));
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.f), glm::vec3(0.5,1,0));
    return model;
}
void GActor::Draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    m_ShaderProgram->UseShader();
    
    glm::mat4 model = GetModelMat();
    m_ShaderProgram->SetUniformMatrix4fv("model", model);
    glm::mat4 view = CameraManager::Get()->GetCamera()->GetViewMatrix();
    m_ShaderProgram->SetUniformMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(CameraManager::Get()->GetCamera()->Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.f);
    m_ShaderProgram->SetUniformMatrix4fv("projection", projection);
    
    
    if (m_Texture_0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture_0);
    }
    if (m_Texture_1)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_Texture_1);
    }if (m_Texture_2)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_Texture_2);
    }if (m_Texture_3)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_Texture_3);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
    
}
