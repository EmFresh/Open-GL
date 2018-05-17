#include "GLSLCompiler.h"

GLSLCompiler::GLSLCompiler() :_attributeNum(0), _programID(0), _vertID(0), _fragID(0)
{

}

GLSLCompiler::~GLSLCompiler()
{}

void GLSLCompiler::compileShaders(const std::string & vertFilePath, const std::string & fragFilePath)
{
	glewInit();
	_programID = glCreateProgram();
	_vertID = glCreateShader(GL_VERTEX_SHADER);
	compileShader(VT_SHADER, vertFilePath, _vertID);

	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(FG_SHADER, fragFilePath, _fragID);
}

void GLSLCompiler::linkShaders()
{
	glAttachShader(_programID, _vertID);
	glAttachShader(_programID, _fragID);

	glLinkProgram(_programID);
	
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if(isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetProgramInfoLog(_programID, maxLength, &maxLength, infoLog);

		// We don't need the program anymore.
		glDeleteProgram(_programID);
		// Don't leak shaders either.
		glDeleteShader(_vertID);
		glDeleteShader(_fragID);

		// Use the infoLog as you see fit.
		_log->writeLog(infoLog + '\n');
		// In this simple program, we'll just leave
		return;
	}
	glDetachShader(_programID, _vertID);
	glDetachShader(_programID, _fragID);
	glDeleteShader(_vertID);
	glDeleteShader(_fragID);
}

void GLSLCompiler::addAtribute(const std::string attributeName, short attribSize)
{
	glBindAttribLocation(_programID, _attributeNum, attributeName.c_str());
	_attributeNum += attribSize;
}

GLint GLSLCompiler::getUniformLocation(const char * uniform)
{
	return glGetUniformLocation(_programID, uniform);
}

void GLSLCompiler::enable()
{
	if(!_enabled)
	{
		findAtributes();
		glUseProgram(_programID);
		for(int a = 0; a < _attributeNum; a++)
			glEnableVertexAttribArray(a);
	}
}

void GLSLCompiler::disable()
{
	if(_enabled)
	{
		glUseProgram(0);
		for(int a = 0; a < _attributeNum; a++)
			glDisableVertexAttribArray(a);
	}
}

void GLSLCompiler::compileShader(Shaders shadNum, const std::string filePath, GLuint id)
{
	std::ifstream
		shader(filePath);

	std::string fileContent = "", line;

	while(std::getline(shader, line))
		fileContent += line + '\n';
	shader.close();

	if(shadNum == VT_SHADER) //stores vtsh
		_vtsh = fileContent;

	const char* tmpFileContent = fileContent.c_str();
	glShaderSource(id, 1, &tmpFileContent, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		char* errorLog = new char[maxLength];
		glGetShaderInfoLog(id, maxLength, &maxLength, errorLog);

		_log->writeLog(errorLog + '\n');
		glDeleteShader(id);

	}
}

void GLSLCompiler::findAtributes()
{
	unsigned short count = 0;
	for(int a = 0; a < _vtsh.size(); a++)
	{
		if(_vtsh.substr(a, 3) == "in ")
		{
			count++;
			a += 3;
		}
	}
	_attributeNum = count;
}

