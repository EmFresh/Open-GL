#include "GLSL_Compiler.h"

GLSL_Compiler::GLSL_Compiler() :m_attributeNum(0),m_programID(0), m_vertID(0), m_fragID(0)
{
	glewInit();
	log->writeLog("Entered constructer\n");
	printf("Entered constructer\n");
}
						 
GLSL_Compiler::~GLSL_Compiler()
{}

void GLSL_Compiler::compileShaders(const std::string & vertFilePath, const std::string & fragFilePath)
{
	m_programID = glCreateProgram();
	m_vertID = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertFilePath, m_vertID);

	m_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragFilePath, m_fragID);	 
}

void GLSL_Compiler::linkShaders()
{
	
	glAttachShader(m_programID, m_vertID);
	glAttachShader(m_programID, m_fragID);

	glLinkProgram(m_programID);
			//error check missing!!!
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if(isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_programID);
		// Don't leak shaders either.
		glDeleteShader(m_vertID);
		glDeleteShader(m_fragID);

		// Use the infoLog as you see fit.
		log->writeLog(infoLog + '\n');
		// In this simple program, we'll just leave
		return;
	}
	glDetachShader(m_programID, m_vertID);
	glDetachShader(m_programID, m_fragID);
	glDeleteShader(m_vertID);
	glDeleteShader(m_fragID);
}

void GLSL_Compiler::addAtribute(const std::string attributeName)
{
	glBindAttribLocation(m_programID, m_attributeNum++, attributeName.c_str());
}

void GLSL_Compiler::enable()
{
	glUseProgram(m_programID);
	for(int a = 0; a < m_attributeNum; a++)
		glEnableVertexAttribArray(a);
}

void GLSL_Compiler::disable()
{
	glUseProgram(0);
	for(int a = 0; a < m_attributeNum; a++)
		glDisableVertexAttribArray(a);
}

void GLSL_Compiler::compileShader(const std::string filePath, GLuint id)
{
	std::ifstream
		vertShader(filePath);
	
	std::string fileContent = "", line;

	while(std::getline(vertShader, line))
		fileContent += line + '\n';	
	vertShader.close();

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
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		
		log->writeLog(errorLog+'\n');
		glDeleteShader(id);
		exit(-556468);
	}
}

