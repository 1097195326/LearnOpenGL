//
//  ShaderProgram.cpp
//  LearnOpenGL
//
//  Created by fafa on 2018/5/9.
//  Copyright © 2018年 hongxing zhang. All rights reserved.
//

#include "ShaderProgram.h"
#include "../Tools/FileHelper.h"


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
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_shaderProgramId);
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

void ShaderProgram::SetAttribute1f(string _name, float _parm)
{
    glVertexAttrib1f(glGetAttribLocation(m_shaderProgramId, _name.c_str()), _parm);
}
void ShaderProgram::SetAttribute3fv(string _name, vec3 _parm)
{
    glVertexAttrib1fv(glGetAttribLocation(m_shaderProgramId, _name.c_str()), glm::value_ptr(_parm));
}
void ShaderProgram::SetUniform1i(std::string _name, int _parm)
{
    glUniform1i(glGetUniformLocation(m_shaderProgramId, _name.c_str()), _parm);
}
void ShaderProgram::SetUniform1f(string _name, float _parm)
{
    glUniform1f(glGetUniformLocation(m_shaderProgramId, _name.c_str()), _parm);
}
void ShaderProgram::SetUniform3fv(string _name, vec3 _parm)
{
    glUniform3fv(glGetUniformLocation(m_shaderProgramId, _name.c_str()), 1, glm::value_ptr(_parm));
}
void ShaderProgram::SetUniformMatrix4fv(string _name, mat4 _parm)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramId, _name.c_str()), 1, false, glm::value_ptr(_parm));
}
void ShaderProgram::SetVertexAttribPointer(string _name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
    GLuint index = glGetAttribLocation(m_shaderProgramId, _name.c_str());
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
void ShaderProgram::SetVertexAttribPointer(int index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
//    GLuint index = glGetAttribLocation(m_shaderProgramId, _name.c_str());
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
