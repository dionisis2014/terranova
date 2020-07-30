#include "engine/shader/shaderManager.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

shaderManager::shaderManager() {
	shaderManagerID = glCreateProgram();

	flagLinked = false;

	for (unsigned int i = 0; i < sizeof(shaderManagerUniformsSpecial) / sizeof(GLint); i++)
		shaderManagerUniformsSpecial[i] = -1;
}

shaderManager::~shaderManager() {
	glDeleteProgram(shaderManagerID);
}

bool shaderManager::attachShader(shaderObject *shader) {
	if (shader == nullptr || flagLinked || !shader->compiled())
		return false;

	shaderManagerShaders.push_back(shader);
	glAttachShader(shaderManagerID, shader->ID());

	return true;
}

bool shaderManager::attachAttrib(GLuint location, std::string name) {
	if (flagLinked)
		return false;

	glBindAttribLocation(shaderManagerID, location, name.c_str());

	return true;
}

bool shaderManager::attachUniform(std::string name, uniformUsage_t usage) {
	if (!flagLinked)
		return false;

	GLint location = glGetUniformLocation(shaderManagerID, name.c_str());
	if (location >= 0) {
		shaderManagerUniforms.push_back( { name, location, usage });

		switch (usage) {
		case UNIFORM_USAGE_MATRIX_MODEL:
			shaderManagerUniformsSpecial[0] = location;
			break;
		case UNIFORM_USAGE_MATRIX_VIEW:
			shaderManagerUniformsSpecial[1] = location;
			break;
		case UNIFORM_USAGE_MATRIX_PROJECTION:
			shaderManagerUniformsSpecial[2] = location;
			break;
		case UNIFORM_USAGE_MATRIX_PROJVIEW:
			shaderManagerUniformsSpecial[3] = location;
			break;
		default:
			break;
		}
	}

	return true;
}

bool shaderManager::pushUniformMatrix(std::string name, glm::mat4 matrix) {
	if (!flagLinked || shaderManagerUniforms.size() == 0)
		return false;

	for (std::size_t i = 0; i < shaderManagerUniforms.size(); i++)
		if (shaderManagerUniforms[i].name == name) {
			glUniformMatrix4fv(shaderManagerUniforms[i].location, 1, GL_FALSE, glm::value_ptr(matrix));

			return true;
		}

	return false;
}

bool shaderManager::pushUniformMatrix(GLint location, glm::mat4 matrix) {
	if (!flagLinked || shaderManagerUniforms.size() == 0 || location < 0)
		return false;

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	return true;
}

bool shaderManager::pushUniformF(std::string name, float value) {
	if (!flagLinked || shaderManagerUniforms.size() == 0)
		return false;

	for (std::size_t i = 0; i < shaderManagerUniforms.size(); i++)
		if (shaderManagerUniforms[i].name == name) {
			glUniform1f(shaderManagerUniforms[i].location, value);

			return true;
		}

	return true;
}

bool shaderManager::pushUniformF(GLint location, float value) {
	if (!flagLinked || shaderManagerUniforms.size() == 0 || location < 0)
		return false;

	glUniform1f(location, value);

	return true;
}

bool shaderManager::pushUniform3F(std::string name, glm::vec3 vector) {
	if (!flagLinked || shaderManagerUniforms.size() == 0)
		return false;

	for (std::size_t i = 0; i < shaderManagerUniforms.size(); i++)
		if (shaderManagerUniforms[i].name == name) {
			glUniform3f(shaderManagerUniforms[i].location, vector.x, vector.y, vector.z);

			return true;
		}

	return true;
}

bool shaderManager::pushUniform3F(GLint location, glm::vec3 vector) {
	if (!flagLinked || shaderManagerUniforms.size() == 0 || location < 0)
		return false;

	glUniform3f(location, vector.x, vector.y, vector.z);

	return true;
}

bool shaderManager::link() {
	if (flagLinked || shaderManagerShaders.size() == 0)
		return false;

	glLinkProgram(shaderManagerID);
	for (std::size_t i = 0; i < shaderManagerShaders.size(); i++)
		glDetachShader(shaderManagerID, shaderManagerShaders[i]->ID());

	flagLinked = true;
	return true;
}

bool shaderManager::use() {
	if (flagLinked) {
		glUseProgram(shaderManagerID);
		return true;
	}

	return false;
}

std::vector<shaderObject*>& shaderManager::shaders() {
	return shaderManagerShaders;
}

GLuint shaderManager::ID() {
	return shaderManagerID;
}

bool shaderManager::linked() {
	return flagLinked;
}

GLint shaderManager::getUniform(std::string name) {
	for (std::size_t i = 0; i < shaderManagerUniforms.size(); i++)
		if (shaderManagerUniforms[i].name == name)
			return shaderManagerUniforms[i].location;

	return -1;
}

GLint shaderManager::getUniform(uniformUsage_t usage) {
	switch (usage) {
	case UNIFORM_USAGE_MATRIX_MODEL:
		return shaderManagerUniformsSpecial[0];
		break;
	case UNIFORM_USAGE_MATRIX_VIEW:
		return shaderManagerUniformsSpecial[1];
		break;
	case UNIFORM_USAGE_MATRIX_PROJECTION:
		return shaderManagerUniformsSpecial[2];
		break;
	case UNIFORM_USAGE_MATRIX_PROJVIEW:
		return shaderManagerUniformsSpecial[3];
		break;
	default:
		for (std::size_t i = 0; i < shaderManagerUniforms.size(); i++)
			if (shaderManagerUniforms[i].usage == usage)
				return shaderManagerUniforms[i].location;
		break;
	}
	return -1;
}
