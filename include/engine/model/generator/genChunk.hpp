#ifndef INCLUDE_ENGINE_MODEL_GENERATOR_GENCHUNK_HPP_
#define INCLUDE_ENGINE_MODEL_GENERATOR_GENCHUNK_HPP_

#include "engine/model/generator/generator.hpp"
#include "engine/world/block.hpp"

const static meshVertex_t MESH_GEN_CHUNK_BLOCK_VERTS[24] = {
		//front
		{ { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ { -0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
		//back
		{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
		{ { -0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
		{ { 0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
		//right
		{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
		//left
		{ { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
		{ { -0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
		{ { -0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
		//top
		{ { -0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
		{ { -0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
		{ { 0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
		//bottom
		{ { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
		{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
};
const static meshVertexElem_t MESH_GEN_CHUNK_BLOCK_ELEMS[36] = {
		//front
		0, 1, 3,
		3, 1, 2,
		//back
		7, 6, 4,
		4, 6, 5,
		//right
		8, 9, 11,
		11, 9, 10,
		//left
		15, 14, 12,
		12, 14, 13,
		//top
		16, 17, 19,
		19, 17, 18,
		//bottom
		23, 22, 20,
		20, 22, 21,

};

class meshGenChunk: public meshGeneratorObject {
protected:
	blockObject *meshGenChunkBlocks;

public:
	meshGenChunk();
	virtual ~meshGenChunk();

	bool generate();
	void setBlocks(blockObject *blocks);
};

#endif
