//
//  GActor.hpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/25.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef GActor_hpp
#define GActor_hpp

#include "GameObject.h"

#include <GLFW/glfw3.h>
//math
#include "../../../glm/glm.hpp"
#include "../../../glm/gtc/matrix_transform.hpp"
#include "../../../glm/gtc/type_ptr.hpp"
//
#include "ShaderProgram.h"
#include "GameHeader.h"
//image


using namespace glm;


class GActor //:  public GameObject
{
private:
    ShaderProgram *         m_ShaderProgram;
    GLuint      m_Shader;
    GLuint      m_VBO;
    
    GLuint      m_Texture_0;
    GLuint      m_Texture_1;
    GLuint      m_Texture_2;
    GLuint      m_Texture_3;
    
    //----class
    vec3        m_Position;
    float       m_Scale;
    vec3 *      m_Data;
    int         m_VertexCount;
private:
    mat4        GetModelMat();
public:
    GActor();
    ~GActor();
    
    void SetData(float vertex[],int size, int count,bool useColor = false);
    
    void SetShader(GLuint _shader);
    void SetShader(string _vertexShader, string _fragmentShader);
    GLuint      GetShader(){return m_Shader;}
    GLuint      GetVBO_Id(){return m_VBO;}
    void SetTexture(string imagePath, int index = 0);
    
    void SetPosition(vec3 pos);
    void SetScale(float scale);
    
    virtual void Draw();
};

#endif /* GActor_hpp */
