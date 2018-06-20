//
//  ShaderProgram.hpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/9.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "GameHeader.h"

#include <GLFW/glfw3.h>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

using namespace glm;

class ShaderProgram
{
private:
    GLuint              m_shaderProgramId;
    
public:
    ShaderProgram(string VertexPath, string FragmentPath);
    
    virtual ~ShaderProgram();
    
    virtual void        Init();
    
    void                UseShader();
    
    GLuint              GetShaderProgramId();
    
    void                SetAttribute1f(string _name, float _parm);
    
    void                SetAttribute3fv(string _name, vec3 _parm);
    
    void                SetUniform1i(string _name, int _parm);
    
    void                SetUniform1f(string _name, float _parm);
    
    void                SetUniform3fv(string _name, vec3 _parm);
    
    void                SetUniformMatrix4fv(string _name, mat4 _parm);
    
    void                SetVertexAttribPointer(string _name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
    
};

#endif /* ShaderProgram_hpp */
