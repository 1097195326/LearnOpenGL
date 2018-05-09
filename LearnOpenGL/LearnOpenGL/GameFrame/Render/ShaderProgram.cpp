//
//  ShaderProgram.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/9.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "ShaderProgram.h"
#include "FileHelper.h"


ShaderProgram::ShaderProgram(string VertexPath, string FragmentPath)
{
    string vertexShaderSource = FileHelper::ReadFileToString(VertexPath);
    string fragmentShaderSource = FileHelper::ReadFileToString(FragmentPath);
    
    const char * vs = vertexShaderSource.c_str();
    const char * fs = fragmentShaderSource.c_str();
    
    GLuint VertexShader,FragmentShader;
    // create vertex shader
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vs, NULL);
    glCompileShader(VertexShader);
    
    int Success;
    char InfoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
        printf("ERROR::SHADER::VERTEX::COMPILE_FAILED : %s",InfoLog);
    }
    // create fragment shader
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fs, NULL);
    glCompileShader(FragmentShader);
    
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILE_FAILED : %s",InfoLog);
    }
    // create shader program
    m_shaderProgramId = glCreateProgram();
    glAttachShader(m_shaderProgramId, VertexShader);
    glAttachShader(m_shaderProgramId, FragmentShader);
    glLinkProgram(m_shaderProgramId);
    
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &Success);
    if(!Success)
    {
        glGetProgramInfoLog(m_shaderProgramId, 512, NULL, InfoLog);
        printf("ERROT::SHADER::PROGRAM::LINK_FAILED : %s",InfoLog);
    }
    // delete vertexShader, fragmentShader
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    
}
void ShaderProgram::Init()
{
    
}
void ShaderProgram::UseShader()
{
    glUseProgram(m_shaderProgramId);
}
GLuint ShaderProgram::GetShaderProgramId()
{
    return m_shaderProgramId;
}
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_shaderProgramId);
}
