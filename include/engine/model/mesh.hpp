#ifndef INCLUDE_ENGINE_MODEL_MESH_HPP_
#define INCLUDE_ENGINE_MODEL_MESH_HPP_

#include "engine/object/objectGeneric.hpp"
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

typedef union {
	struct {
		GLfloat xyz[3];
	};
	GLfloat x;
	GLfloat y;
	GLfloat z;
} meshVertexPos_t;

typedef union {
	struct {
		GLfloat rgb[3];
	};
	GLfloat r;
	GLfloat g;
	GLfloat b;
} meshVertexCol_t;

typedef union {
	struct {
		GLfloat xyz[3];
	};
	GLfloat x;
	GLfloat y;
	GLfloat z;
} meshVertexNorm_t;

typedef struct {
	meshVertexPos_t position;
	meshVertexCol_t color;
	meshVertexNorm_t normal;
} meshVertex_t;

typedef GLuint meshVertexElem_t;

typedef enum {
	MESH_ATTRIB_FLOAT,
	MESH_ATTRIB_BYTE,
	MESH_ATTRIB_UBYTE,
	MESH_ATTRIB_INT,
	MESH_ATTRIB_UINT
} meshAttribType_t;

class meshObject: public objectGeneric {
protected:
	GLuint meshObjectID;
	GLuint meshObjectVbo;
	glm::mat4 meshObjectMatrix;
	std::size_t meshObjectVertices;

public:
	meshObject();
	virtual ~meshObject();

	bool push(std::vector<meshVertex_t> &vertices);
	bool push(meshVertex_t *vertices, std::size_t size);
	void attribEnable(GLuint attrib);
	void attribDisable(GLuint attrib);
	void attribSet(GLuint attrib, meshAttribType_t attribType, GLuint count, void *offset);
	void setMatrix(glm::mat4 matrix);
	void bind();
	void unbind();

	GLuint vbo();
	GLuint id();
	glm::mat4 getMatrix();
	std::size_t getVerts();
};

class meshObjectIndexed: public meshObject {
protected:
	GLuint meshObjectIndexedEbo;
	std::size_t meshObjectIndexedElements;

	using meshObject::push;

public:
	meshObjectIndexed();
	virtual ~meshObjectIndexed();

	bool push(std::vector<meshVertex_t> &vertices, std::vector<meshVertexElem_t> &elements);
	bool push(meshVertex_t *vertices, std::size_t sizeVert, meshVertexElem_t *elements, std::size_t sizeElem);

	GLuint ebo();
	std::size_t getElems();
};

#endif
