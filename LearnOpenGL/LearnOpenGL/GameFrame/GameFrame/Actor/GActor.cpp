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
    m_Scale = 1.f;
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
    
    printf("zhx : veo id : %d\n",m_VBO);
}
void GActor::SetShader(std::string _vertexShader, std::string _fragmentShader,bool useColor, bool userTexture)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    m_ShaderProgram = new ShaderProgram(_vertexShader.c_str(),_fragmentShader.c_str());
    
    m_Shader = m_ShaderProgram->GetShaderProgramId();
    
    glUseProgram(m_Shader);
    
    printf("zhx : shader id : %d\n",m_Shader);
    int strip = 3;
    if (useColor)
    {
        strip += 3;
    }
    if (userTexture)
    {
        strip += 2;
    }
    
    GLuint aPos;
    aPos = glGetAttribLocation(m_Shader, "aPos");
    
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(aPos);
    
    if (useColor)
    {
        GLuint aColor;
        aColor = glGetAttribLocation(m_Shader, "aColor");
        
        glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(aColor);
    }
    if(userTexture)
    {
        int offset = useColor ? 5 : 3;
        GLuint aCooPos;
        aCooPos = glGetAttribLocation(m_Shader, "aCooPos");
        
        glVertexAttribPointer(aCooPos, 2, GL_FLOAT, GL_FALSE, strip * sizeof(GL_FLOAT), (GLvoid*)(offset * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(aCooPos);
        
        glUniform1i(glGetUniformLocation(m_Shader, "texture1"), 0);
        glUniform1i(glGetUniformLocation(m_Shader, "texture2"), 1);
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
void GActor::SetScale(float scale)
{
    m_Scale = scale;
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
    
    glUseProgram(m_Shader);
    
    glm::mat4 model = GetModelMat();
    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    
    glm::mat4 view = CameraManager::Get()->GetCamera()->GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    glm::mat4 projection = glm::perspective(glm::radians(CameraManager::Get()->GetCamera()->Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.f);
    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    
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
    
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}
