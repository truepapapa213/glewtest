#include "shader.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;


const int PROGRAM = 0;


Shader::Shader(const char* vFilename, const char* fFilename)
	{
		GLuint vShader = loadShader(vFilename, GL_VERTEX_SHADER);
		GLuint fShader = loadShader(fFilename, GL_FRAGMENT_SHADER);
		ID = makeProgram(vShader, fShader);
		//ID=program;
	}

GLuint Shader::loadShader(const char* filename, GLenum type)
	{
		char* source;
		GLuint shader;
		source = loadShaderFromFile(filename);
		if (source == nullptr)
			return 0;
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		if (!getCompileStatus(shader, false))
		{
			printInfoLog(shader, type);
			glDeleteShader(type);
			return 0;
		}
		delete[] source;
		return shader;
	}

	char* Shader::loadShaderFromFile(const char* filename)
	{
		std::ifstream fin;
		int size;
		char* source;
		fin.open(filename);
		if (!fin.is_open())
		{
			cout << "Cannot open shader file " << filename << " (maybe not exist)!\n";
			return nullptr;
		}
		fin.seekg(0, std::ios_base::end);
		size = fin.tellg();
		source = new char[size + 1]{ '\0' };
		fin.seekg(0, std::ios_base::beg);
		fin.read(source, size);
		fin.close();
		return source;
	}

	GLuint Shader::makeProgram(GLuint vShader, GLuint fShader)
	{
		if (vShader == 0 || fShader == 0)
			return 0;
		GLuint program = glCreateProgram();
		glAttachShader(program, vShader);
		glAttachShader(program, fShader);
		glLinkProgram(program);
		if (!getCompileStatus(program, true))
		{
			printInfoLog(program, PROGRAM);
			program = 0;
		}
		glDeleteShader(vShader);
		glDeleteShader(fShader);
		return program;
	}

	bool Shader::getCompileStatus(GLuint id, bool isProgram)
	{
		GLint status;
		if (isProgram)
			glGetProgramiv(id, GL_LINK_STATUS, &status);
		else
			glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		return status;// == GL_TRUE;
	}

	void Shader::printInfoLog(GLuint id, GLenum type)
	{
		char* infoLog;
		int len;

		if (type == PROGRAM)
		{
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
			infoLog = new char[len + 1];
			glGetProgramInfoLog(id, len + 1, nullptr, infoLog);
			cout << "Program linking failed, info log:\n" << infoLog << endl;
		}
		else
		{
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			infoLog = new char[len + 1];
			glGetShaderInfoLog(id, len + 1, nullptr, infoLog);
			cout << "Shader compilation failed, type: " << getShaderName(type) << ", info log:\n" << infoLog << endl;
		}

		delete[] infoLog;
	}

	const char* Shader::getShaderName(GLenum type)
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:
			return "vertex";
		case GL_FRAGMENT_SHADER:
			return "fragment";
		default:
			return "UNKNOWN";
		}
	}


