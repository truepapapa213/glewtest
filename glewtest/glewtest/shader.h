
#ifndef SHADER_H_
#define SHADER_H_
#include <GL/glew.h>
class Shader {
public:
	
	GLuint ID;


	Shader(const char* vFilename, const char* fFilename);

private:
	GLuint loadShader(const char* filename, GLenum type);
	char* loadShaderFromFile(const char* filename);
	GLuint makeProgram(GLuint vShader, GLuint fShader);
	bool getCompileStatus(GLuint id, bool isProgram);
	void printInfoLog(GLuint id, GLenum type);
	const char* getShaderName(GLenum type);

private:
	
};

#endif