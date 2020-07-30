#include "engine/model/mesh.hpp"

meshObject::meshObject() {
	glGenBuffers(1, &meshObjectVbo);
	glGenVertexArrays(1, &meshObjectID);
	meshObjectMatrix = glm::mat4(1.0f);
	meshObjectVertices = 0;
}

meshObject::~meshObject() {
	glDeleteBuffers(1, &meshObjectVbo);
	glDeleteVertexArrays(1, &meshObjectID);
}

bool meshObject::push(std::vector<meshVertex_t> &vertices) {
	return push(vertices.data(), vertices.size());
}

bool meshObject::push(meshVertex_t *vertices, std::size_t size) {
	if (size < 1)
		return false;

	meshObjectVertices = size;

	glBindVertexArray(meshObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, meshObjectVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(meshVertex_t) * size, vertices, GL_STATIC_DRAW);

	return true;
}

void meshObject::attribEnable(GLuint attrib) {
	glBindVertexArray(meshObjectVbo);
	glEnableVertexAttribArray(attrib);
}

void meshObject::attribDisable(GLuint attrib) {
	glBindVertexArray(meshObjectVbo);
	glDisableVertexAttribArray(attrib);
}

void meshObject::attribSet(GLuint attrib, meshAttribType_t attribType, GLuint count, void *offset) {
	glBindVertexArray(meshObjectVbo);
	switch (attribType) {
	case MESH_ATTRIB_FLOAT:
		glVertexAttribPointer(attrib, count, GL_FLOAT, GL_FALSE, sizeof(meshVertex_t), offset);
		break;
	case MESH_ATTRIB_BYTE:
		glVertexAttribIPointer(attrib, count, GL_BYTE, sizeof(meshVertex_t), offset);
		break;
	case MESH_ATTRIB_UBYTE:
		glVertexAttribIPointer(attrib, count, GL_UNSIGNED_BYTE, sizeof(meshVertex_t), offset);
		break;
	case MESH_ATTRIB_INT:
		glVertexAttribIPointer(attrib, count, GL_INT, sizeof(meshVertex_t), offset);
		break;
	case MESH_ATTRIB_UINT:
		glVertexAttribIPointer(attrib, count, GL_UNSIGNED_INT, sizeof(meshVertex_t), offset);
		break;
	}
}

void meshObject::setMatrix(glm::mat4 matrix) {
	meshObjectMatrix = matrix;
}

std::size_t meshObject::getVerts() {
	return meshObjectVertices;
}

void meshObject::bind() {
	glBindVertexArray(meshObjectID);
}

void meshObject::unbind() {
	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindVertexArray(0);
}

GLuint meshObject::vbo() {
	return meshObjectVbo;
}

GLuint meshObject::id() {
	return meshObjectID;
}

glm::mat4 meshObject::getMatrix() {
	return meshObjectMatrix;
}

meshObjectIndexed::meshObjectIndexed() :
		meshObject() {
	glGenBuffers(1, &meshObjectIndexedEbo);
	meshObjectIndexedElements = 0;
}

meshObjectIndexed::~meshObjectIndexed() {
	glDeleteBuffers(1, &meshObjectIndexedEbo);
}

bool meshObjectIndexed::push(std::vector<meshVertex_t> &vertices, std::vector<meshVertexElem_t> &elements) {
	return push(vertices.data(), vertices.size(), elements.data(), elements.size());
}

bool meshObjectIndexed::push(meshVertex_t *vertices, std::size_t sizeVert, meshVertexElem_t *elements, std::size_t sizeElem) {
	if (sizeVert < 1 || sizeElem < 1)
		return false;

	meshObjectVertices = sizeVert;
	meshObjectIndexedElements = sizeElem;

	glBindVertexArray(meshObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, meshObjectVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(meshVertex_t) * sizeVert, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshObjectIndexedEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(meshVertexElem_t) * sizeElem, elements, GL_STATIC_DRAW);

	return true;
}

GLuint meshObjectIndexed::ebo() {
	return meshObjectIndexedEbo;
}

std::size_t meshObjectIndexed::getElems() {
	return meshObjectIndexedElements;
}
