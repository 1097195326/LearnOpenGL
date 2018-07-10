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
//#include "../glm/glm.hpp"
//#include "../glm/gtc/matrix_transform.hpp"
//#include "../glm/gtc/type_ptr.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//
#include "ShaderProgram.h"
#include "GameHeader.h"
//image


using namespace glm;


class GActor //:  public GameObject
{
private:
    ShaderProgram *         m_ShaderProgram;
    
    GLuint      m_VBO;
    unsigned int m_VAO;
    
    GLuint      m_Texture_0;
    GLuint      m_Texture_1;
    GLuint      m_Texture_2;
    GLuint      m_Texture_3;
    //
    bool        m_IsUseColor;
    bool        m_IsUseTexture;
    //----class
    vec3        m_Position;
    vec3        m_Scale;
    vec3        m_Color;
    vec3 *      m_Data;
    
    int         m_VertexCount;
private:
    mat4        GetModelMat();
public:
    GActor();
    ~GActor();
    
    void        SetData(float vertex[],int size, int count);
    
    void        SetShader(string _vertexShader, string _fragmentShader, bool _haveNormal = false, bool _haveColor = false, bool _haveTexture = false);
    
    GLuint      GetVBO_Id(){return m_VBO;}
    
    void        SetTexture(string imagePath, int index = 0);
    
    void        SetPosition(vec3 pos);
    vec3        GetPosition();
    
    void        SetScale(float scale);
    void        SetScele(vec3 scale);
    
    void        SetColor(float color);
    void        SetColor(vec3 color);
    
    
    void        SetLightColor(float color);
    void        SetLightColor(vec3 color);
    
    void        SetLightPosition(vec3 position);
    
    virtual void Draw();
    
    ShaderProgram * GetShader();
};

#endif /* GActor_hpp */
