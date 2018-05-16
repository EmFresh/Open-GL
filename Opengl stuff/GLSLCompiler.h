#pragma once
#include "GL\glew.h"
#include <string>
#include <fstream>
#include "Logger.h"

class GLSLCompiler
{
public:
	GLSLCompiler();
	~GLSLCompiler();

	//compiles shaders into code
	void compileShaders(const std::string& vertFilePath, const std::string& fragFilePath);
	//links vertx and fragment shaders into a single shader
	void linkShaders();	   
	/*
	adds atributes to the shader
    (ONLY USE if in-shader indexes are not specified)
	*/
	void addAtribute(const std::string attributeName, short attribSize = 1);

	GLint getUniformLocation(const char *uniform);

	//enables shader program for use
	void enable();
	//disables shader program 
	void disable();

private:
	enum Shaders
	{
		VT_SHADER,
		FG_SHADER
	};

	void compileShader(Shaders shadNum, const std::string filePath, GLuint id);
	void findAtributes();

	std::string _vtsh;
	int _attributeNum;
	bool _enabled=0;
	GLuint _programID;
	GLuint _vertID;
	GLuint _fragID;
	Logger *_log = new Logger("ShaderLog");
};


