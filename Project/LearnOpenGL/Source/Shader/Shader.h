#pragma once


#include "../Headle.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;

class Shader
{
private:
	GLuint              ID;
	string				Name;
public:
	Shader(string shaderName, string VertexPath, string FragmentPath);

	virtual ~Shader();

	virtual void        Init();

	void                Use();

	GLuint              GetID();

	void                SetAttribute1f(string _name, float _parm);

	void                SetAttribute3fv(string _name, vec3 _parm);

	void                SetUniform1i(string _name, int _parm);

	void                SetUniform1f(string _name, float _parm);

	void                SetUniform3fv(string _name, vec3 _parm);

	void                SetUniformMatrix4fv(string _name, mat4 _parm);

	/*void                SetVertexAttribPointer(string _name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);

	void                SetVertexAttribPointer(int index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
*/
};