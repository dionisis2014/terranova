#ifndef INCLUDE_ENGINE_MODEL_GENERATOR_GENCHUNK_HPP_
#define INCLUDE_ENGINE_MODEL_GENERATOR_GENCHUNK_HPP_

#include "engine/model/generator/generator.hpp"
#include "engine/world/block.hpp"

const static meshVertex_t MESH_GEN_CHUNK_BLOCK_VERTS[24] = {
		//front
		{ { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
		{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
		//right
		{ { 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
		//back
		{ { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
		{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } },
		{ { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } },
		{ { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
		//left
		{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
		{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } },
		{ { 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } },
		{ { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
		//top
		{ { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
		{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
		{ { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
		{ { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
		//bottom
		{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
		{ { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } },
		{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } },
		{ { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
};
const static meshVertexElem_t MESH_GEN_CHUNK_BLOCK_ELEMS[36] = {
		//front
		0, 1, 3,
		3, 1, 2,
		//right
		4, 5, 7,
		7, 5, 6,
		//back
		8, 9, 11,
		11, 9, 10,
		//left
		12, 13, 15,
		15, 13, 14,
		//top
		16, 17, 19,
		19, 17, 18,
		//bottom
		20, 21, 23,
		23, 21, 22
};

class meshGenChunk: public meshGeneratorObject {
protected:
	blockObject **meshGenChunkBlocks;

public:
	meshGenChunk();
	virtual ~meshGenChunk();

	bool generate();
	void setBlocks(blockObject **blocks);
};

#endif
