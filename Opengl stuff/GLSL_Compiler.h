#pragma once
#include "GL\glew.h"#include <string>
#include <fstream>
#include "Logger.h"

class GLSL_Compiler
{
public:
	GLSL_Compiler();
	~GLSL_Compiler();

	//compiles shaders into code
	void compileShaders(const std::string& vertFilePath, const std::string& fragFilePath);
	//links shaders into single shader
	void linkShaders();

	void addAtribute(const std::string attributeName);

	void enable();
	void disable();

private:
	void compileShader(const std::string filePath, GLuint id);

	int m_attributeNum;
	GLuint m_programID;
	GLuint m_vertID;
	GLuint m_fragID;
	Logger *log=new Logger("ShaderLog");
};


