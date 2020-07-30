#include "engine/world/chunk.hpp"

chunkObject::chunkObject() {
	chunkObjectBlocks = new blockObject[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
}

chunkObject::~chunkObject() {
	delete[] chunkObjectBlocks;
}

bool chunkObject::generateMesh() {
	chunkObjectMeshGen.setBlocks(chunkObjectBlocks);
	if (!chunkObjectMeshGen.generate())
		return false;

	return true;
}

std::vector<meshVertex_t>& chunkObject::meshVerts() {
	return chunkObjectMeshGen.vertices();
}

std::vector<meshVertexElem_t>& chunkObject::meshElems() {
	return chunkObjectMeshGen.elements();
}
