#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

char *textFileRead(const char *fn);  

#define WINDOW_PLATFORM


class OGLShader 
{

public:
	OGLShader(){}
	~OGLShader(){}
	OGLShader(std::string shaderName):name(shaderName) {}

public:
	void init();
	void attach(int type, char *filename);
	void link();
	void interfaceInfo();

	void use(void) 
	{
		glUseProgram(program);
	}
	void end(void) 
	{
		glUseProgram(0);
	}

	GLuint GetProgram()
	{
        return program;
	}

private:
	std::vector<GLuint> handles; //OGLShader handle
	GLuint program;   //OGLShader program
	std::string name;   //OGLShader class name
};

#endif

