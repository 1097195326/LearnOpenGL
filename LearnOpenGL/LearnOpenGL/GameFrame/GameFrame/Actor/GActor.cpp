//
//  GActor.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "GActor.h"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void GActor::SetData(float vertex[],int size, int count,bool useColor)
{
    m_VertexCount = count;
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GActor::SetShader(GLuint shader)
{
    m_Shader = shader;
}
void GActor::SetShader(std::string _vertexShader, std::string _fragmentShader)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    ShaderProgram mShaderProgram("Shaders/VertexShader.strings","Shaders/FragmentShader.strings");
    
    m_Shader = mShaderProgram.GetShaderProgramId();
    
    GLuint aPos;
    aPos = glGetAttribLocation(m_Shader, "aPos");
    glEnableVertexAttribArray(aPos);
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
    
    GLuint aCooPos;
    aCooPos = glGetAttribLocation(m_Shader, "aCooPos");
    glEnableVertexAttribArray(aCooPos);
    glVertexAttribPointer(aCooPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    
    glUseProgram(m_Shader);
    
    glUniform1i(glGetUniformLocation(m_Shader, "texture1"), 0);
    glUniform1i(glGetUniformLocation(m_Shader, "texture2"), 1);
    
}
void GActor::SetTexture(std::string imagePath, int index)
{
    
    switch (index) {
        case 0:
            glGenTextures(1, &m_Texture_0);
            glBindTexture(GL_TEXTURE_2D, m_Texture_0);
            break;
        case 1:
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
void GActor::SetScale(float scale)
{
    m_Scale = scale;
}
mat4 GActor::GetModelMat()
{
    mat4 model(1);
    model = glm::translate(model, m_Position);
    model = glm::scale(model, vec3(m_Scale));
    return model;
}
void GActor::Draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
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
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
