#include "engine/shader/shader.hpp"
#include <vector>
#include "engine/io/file/loader.hpp"
#include <iostream>

shaderObject::shaderObject() {
	shaderObjectID = 0;
	shaderObjectType = SHADER_VERTEX;

	flagCompiled = false;
}

shaderObject::~shaderObject() {

}

bool shaderObject::compile(std::string filename, shaderType_t type) {
	if (flagCompiled)
		return false;

	std::vector<GLchar> shaderCode(0);
	if (!ioFileLoad(filename, shaderCode, false)) {
		std::cerr << "Failed to load shader file '" << filename << "'!" << std::endl;
		return false;
	}

	switch (type) {
	case SHADER_VERTEX:
		shaderObjectID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case SHADER_FRAGMENT:
		shaderObjectID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	GLchar *shaderCodePtr = shaderCode.data();
	glShaderSource(shaderObjectID, 1, &shaderCodePtr, nullptr);
	glCompileShader(shaderObjectID);

	GLint success;
	glGetShaderiv(shaderObjectID, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		std::cerr << "Failed to compile shader code for file '" << filename << "'!" << std::endl;
		GLint logLen;
		glGetShaderiv(shaderObjectID, GL_INFO_LOG_LENGTH, &logLen);
		char *log = new char[logLen + 1];
		glGetShaderInfoLog(shaderObjectID, logLen, nullptr, log);
		std::cerr << log << std::endl;
		delete[] log;

		vacuum();
		return false;
	}

	flagCompiled = true;
	return true;
}

void shaderObject::vacuum() {
	if (shaderObjectID) {
		glDeleteShader(shaderObjectType);
		flagCompiled = false;
	}
}

GLuint shaderObject::ID() {
	return shaderObjectID;
}

bool shaderObject::compiled() {
	return flagCompiled;
}
