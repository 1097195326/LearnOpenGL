
#include "Shader.h"


Shader::Shader(string shaderName, string VertexPath, string FragmentPath)
{
	Name = shaderName;

	string vertexShaderSource = FileHelper::ReadFileToString(VertexPath);
	string fragmentShaderSource = FileHelper::ReadFileToString(FragmentPath);

	const char * vs = vertexShaderSource.c_str();
	const char * fs = fragmentShaderSource.c_str();

	GLuint VertexShader, FragmentShader;
	// create vertex shader
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vs, NULL);
	glCompileShader(VertexShader);

	int Success;
	char InfoLog[512];
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
		printf("ERROR::SHADER::VERTEX::COMPILE_FAILED : %s", InfoLog);
	}
	// create fragment shader
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fs, NULL);
	glCompileShader(FragmentShader);

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILE_FAILED : %s", InfoLog);
	}
	// create shader program
	ID = glCreateProgram();
	glAttachShader(ID, VertexShader);
	glAttachShader(ID, FragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &Success);
	if (!Success)
	{
		glGetProgramInfoLog(ID, 512, NULL, InfoLog);
		printf("ERROT::SHADER::PROGRAM::LINK_FAILED : %s", InfoLog);
	}
	// delete vertexShader, fragmentShader
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

}
Shader::~Shader()
{
	glDeleteProgram(ID);
}
void Shader::Init()
{

}
void Shader::Use()
{
	glUseProgram(ID);
}
GLuint Shader::GetID()
{
	return ID;
}

void Shader::SetAttribute1f(string _name, float _parm)
{
	glVertexAttrib1f(glGetAttribLocation(ID, _name.c_str()), _parm);
}
void Shader::SetAttribute3fv(string _name, vec3 _parm)
{
	glVertexAttrib1fv(glGetAttribLocation(ID, _name.c_str()), glm::value_ptr(_parm));
}
void Shader::SetUniform1i(std::string _name, int _parm)
{
	glUniform1i(glGetUniformLocation(ID, _name.c_str()), _parm);
}
void Shader::SetUniform1f(string _name, float _parm)
{
	glUniform1f(glGetUniformLocation(ID, _name.c_str()), _parm);
}
void Shader::SetUniform3fv(string _name, vec3 _parm)
{
	glUniform3fv(glGetUniformLocation(ID, _name.c_str()), 1, glm::value_ptr(_parm));
}
void Shader::SetUniformMatrix4fv(string _name, mat4 _parm)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, _name.c_str()), 1, false, glm::value_ptr(_parm));
}
//void Shader::SetVertexAttribPointer(string _name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
//{
//	GLuint index = glGetAttribLocation(m_shaderProgramId, _name.c_str());
//	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
//	glEnableVertexAttribArray(index);
//}
//void Shader::SetVertexAttribPointer(int index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
//{
//	//    GLuint index = glGetAttribLocation(m_shaderProgramId, _name.c_str());
//	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
//	glEnableVertexAttribArray(index);
//}
