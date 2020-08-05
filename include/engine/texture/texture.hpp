#ifndef INCLUDE_ENGINE_TEXTURE_TEXTURE_HPP_
#define INCLUDE_ENGINE_TEXTURE_TEXTURE_HPP_

#include "engine/object/objectGeneric.hpp"
#include <string>
#include <GL/glew.h>

class textureObject: public objectGeneric {
protected:
	GLuint textureObjectID;
	int textureObjectWidth;
	int textureObjectHeight;
	unsigned char *textureObjectData;

public:
	textureObject();
	virtual ~textureObject();

	bool load(std::string filename);
	bool push();
	void bind();

	GLuint id();
	int width();
	int height();
	unsigned char *data();
};

#endif
