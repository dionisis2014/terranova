#include "engine/texture/texture.hpp"
#include <SOIL/SOIL.h>

textureObject::textureObject() {
	glGenTextures(1, &textureObjectID);
	textureObjectWidth = -1;
	textureObjectHeight = -1;
	textureObjectData = nullptr;
}

textureObject::~textureObject() {
	if (textureObjectData != nullptr)
		SOIL_free_image_data(textureObjectData);
	glDeleteTextures(1, &textureObjectID);
}

bool textureObject::load(std::string filename) {
	if (textureObjectData != nullptr)
		SOIL_free_image_data(textureObjectData);
	textureObjectData = SOIL_load_image(filename.c_str(), &textureObjectWidth, &textureObjectHeight, nullptr, SOIL_LOAD_RGB);
	if (textureObjectData == nullptr) {
		textureObjectWidth = -1;
		textureObjectHeight = -1;
		return false;
	}

	return true;
}

bool textureObject::push() {
	if (textureObjectData == nullptr || textureObjectWidth < 1 || textureObjectHeight < 1)
		return false;

	glBindTexture(GL_TEXTURE_2D, textureObjectID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureObjectWidth, textureObjectHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureObjectData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

void textureObject::bind() {
	glBindTexture(GL_TEXTURE_2D, textureObjectID);
}

GLuint textureObject::id() {
	return textureObjectID;
}

int textureObject::width() {
	return textureObjectWidth;
}

int textureObject::height() {
	return textureObjectHeight;
}

unsigned char* textureObject::data() {
	return textureObjectData;
}
