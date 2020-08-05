#include "engine/world/chunk.hpp"

chunkObject::chunkObject() {
	chunkObjectBlocks = new blockObject*[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	for (unsigned int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
		chunkObjectBlocks[i] = nullptr;
}

chunkObject::~chunkObject() {
	for (unsigned int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
		if (chunkObjectBlocks[i] != nullptr)
			delete chunkObjectBlocks[i];
	delete[] chunkObjectBlocks;
}

bool chunkObject::generateMesh() {
	chunkObjectMeshGen.setBlocks(chunkObjectBlocks);
	if (!chunkObjectMeshGen.generate())
		return false;

	return true;
}

void chunkObject::setBlock(blockObject *block, unsigned int x, unsigned int y, unsigned int z) {
	unsigned int pos = (z % CHUNK_SIZE) * CHUNK_SIZE * CHUNK_SIZE + (y % CHUNK_SIZE) * CHUNK_SIZE + x % CHUNK_SIZE;
	if (chunkObjectBlocks[pos] != nullptr)
		delete chunkObjectBlocks[pos];
	chunkObjectBlocks[pos] = block;
}

void chunkObject::removeBlock(unsigned int x, unsigned int y, unsigned int z) {
	unsigned int pos = (z % CHUNK_SIZE) * CHUNK_SIZE * CHUNK_SIZE + (y % CHUNK_SIZE) * CHUNK_SIZE + x % CHUNK_SIZE;
	if (chunkObjectBlocks[pos] == nullptr)
		return;
	delete chunkObjectBlocks[pos];
	chunkObjectBlocks[pos] = nullptr;
}

blockObject* chunkObject::getBlock(unsigned int x, unsigned int y, unsigned int z) {
	return chunkObjectBlocks[(z % CHUNK_SIZE) * CHUNK_SIZE * CHUNK_SIZE + (y % CHUNK_SIZE) * CHUNK_SIZE + x % CHUNK_SIZE];
}

std::vector<meshVertex_t>& chunkObject::meshVerts() {
	return chunkObjectMeshGen.vertices();
}

std::vector<meshVertexElem_t>& chunkObject::meshElems() {
	return chunkObjectMeshGen.elements();
}
