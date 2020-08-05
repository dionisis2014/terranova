#ifndef INCLUDE_ENGINE_SHADER_SHADERMANAGER_HPP_
#define INCLUDE_ENGINE_SHADER_SHADERMANAGER_HPP_

#include "engine/object/objectGeneric.hpp"
#include <GL/glew.h>
#include "engine/shader/shader.hpp"
#include <vector>
#include <map>
#include <glm/glm.hpp>

typedef enum {
	UNIFORM_USAGE_MATRIX_MODEL,
	UNIFORM_USAGE_MATRIX_VIEW,
	UNIFORM_USAGE_MATRIX_PROJECTION,
	UNIFORM_USAGE_MATRIX_PROJVIEW,

	UNIFORM_USAGE_LIGHT_AMBIENT,
	UNIFORM_USAGE_LIGHT_AMBIENT_COLOR,

	UNIFORM_USAGE_TEXTURE,

	UNIFORM_USAGE_GENERIC,

	UNIFORM_USAGE_MAX
} uniformUsage_t;

typedef struct {
	std::string name;
	GLint location;
	uniformUsage_t usage;
} uniform_t;

class shaderManager: public objectGeneric {
private:
	bool flagLinked;

protected:
	GLuint shaderManagerID;
	std::vector<shaderObject*> shaderManagerShaders;
	std::vector<uniform_t> shaderManagerUniforms;

	GLint shaderManagerUniformsSpecial[UNIFORM_USAGE_MAX - 1];

public:
	shaderManager();
	virtual ~shaderManager();

	bool attachShader(shaderObject *shader);
	bool attachAttrib(GLuint location, std::string name);
	bool attachUniform(std::string name, uniformUsage_t usage);
	bool pushUniformMatrix(std::string name, glm::mat4 matrix);
	bool pushUniformMatrix(GLint location, glm::mat4 matrix);
	bool pushUniformF(std::string name, float value);
	bool pushUniformF(GLint location, float value);
	bool pushUniform3F(std::string name, glm::vec3 vector);
	bool pushUniform3F(GLint location, glm::vec3 vector);
	bool pushUniform1I(std::string name, int value);
	bool pushUniform1I(GLint location, int value);
	bool link();
	bool use();

	std::vector<shaderObject*>& shaders();
	GLuint ID();
	bool linked();
	GLint getUniform(std::string name);
	GLint getUniform(uniformUsage_t usage);
};

#endif
