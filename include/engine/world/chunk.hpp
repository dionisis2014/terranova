#ifndef INCLUDE_ENGINE_WORLD_CHUNK_HPP_
#define INCLUDE_ENGINE_WORLD_CHUNK_HPP_

#include "engine/object/objectGeneric.hpp"
#include "engine/world/block.hpp"
#include "engine/model/mesh.hpp"
#include "engine/model/generator/genChunk.hpp"

#define CHUNK_SIZE		4

class chunkObject: public objectGeneric {
protected:
	blockObject *chunkObjectBlocks;
	meshGenChunk chunkObjectMeshGen;

public:
	chunkObject();
	virtual ~chunkObject();

	bool generateMesh();

	std::vector<meshVertex_t>& meshVerts();
	std::vector<meshVertexElem_t>& meshElems();
};

#endif
