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


class ShaderProgram
{
private:
    GLuint m_shaderProgramId;
    
public:
    ShaderProgram(string VertexPath, string FragmentPath);
    virtual ~ShaderProgram();
    
    virtual void Init();
    
    void UseShader();
    GLuint  GetShaderProgramId();
    
};

#endif /* ShaderProgram_hpp */
