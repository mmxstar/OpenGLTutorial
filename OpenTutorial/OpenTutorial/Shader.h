#ifndef  SHADER_H
#define  SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader 
{
public:
	
	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);

	inline GLuint GetProgram() { return m_program; }
	void Use();

private:
	GLuint m_program;//shader program id
};


#endif // ! SHADER_H

