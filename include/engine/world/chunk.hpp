#ifndef INCLUDE_ENGINE_WORLD_CHUNK_HPP_
#define INCLUDE_ENGINE_WORLD_CHUNK_HPP_

#include "engine/object/objectGeneric.hpp"
#include "engine/world/block.hpp"
#include "engine/model/mesh.hpp"
#include "engine/model/generator/genChunk.hpp"

#define CHUNK_SIZE		16

class chunkObject: public objectGeneric {
protected:
	blockObject **chunkObjectBlocks;
	meshGenChunk chunkObjectMeshGen;

public:
	chunkObject();
	virtual ~chunkObject();

	bool generateMesh();
	void setBlock(blockObject *block, unsigned int x, unsigned int y, unsigned int z);
	void removeBlock(unsigned int x, unsigned int y, unsigned int z);

	blockObject* getBlock(unsigned int x, unsigned int y, unsigned int z);

	std::vector<meshVertex_t>& meshVerts();
	std::vector<meshVertexElem_t>& meshElems();
};

#endif
