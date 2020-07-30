#ifndef INCLUDE_ENGINE_SHADER_SHADER_HPP_
#define INCLUDE_ENGINE_SHADER_SHADER_HPP_

#include "engine/object/objectGeneric.hpp"
#include <GL/glew.h>
#include <string>

typedef enum {
	SHADER_VERTEX,
	SHADER_FRAGMENT
} shaderType_t;

class shaderObject: public objectGeneric {
private:
	bool flagCompiled;

protected:
	GLuint shaderObjectID;
	shaderType_t shaderObjectType;

public:
	shaderObject();
	virtual ~shaderObject();

	bool compile(std::string filename, shaderType_t type);
	void vacuum();

	GLuint ID();
	bool compiled();
};

#endif
