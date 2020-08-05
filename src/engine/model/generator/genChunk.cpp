#include "engine/model/generator/genChunk.hpp"
#include "engine/world/chunk.hpp"

meshGenChunk::meshGenChunk() {
	meshGenChunkBlocks = nullptr;
}

meshGenChunk::~meshGenChunk() {

}

bool meshGenChunk::generate() {
	if (meshGenChunkBlocks == nullptr)
		return false;

	meshGeneratorObjectData.clear();
	meshGeneratorObjectElem.clear();

	unsigned int count = 0;
	meshVertex_t vert;

	for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
		for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
			for (unsigned int x = 0; x < CHUNK_SIZE; x++) {

				if (meshGenChunkBlocks[z * CHUNK_SIZE * CHUNK_SIZE + y * CHUNK_SIZE + x] != nullptr) {
					for (unsigned int i = 0; i < 24; i++) {
						vert.position.x = MESH_GEN_CHUNK_BLOCK_VERTS[i].position.x + (GLfloat) x;
						vert.position.y = MESH_GEN_CHUNK_BLOCK_VERTS[i].position.y + (GLfloat) y;
						vert.position.z = MESH_GEN_CHUNK_BLOCK_VERTS[i].position.z + (GLfloat) z;
						vert.uv.u = MESH_GEN_CHUNK_BLOCK_VERTS[i].uv.u;
						vert.uv.v = MESH_GEN_CHUNK_BLOCK_VERTS[i].uv.v;
						vert.normal.x = MESH_GEN_CHUNK_BLOCK_VERTS[i].normal.x;
						vert.normal.y = MESH_GEN_CHUNK_BLOCK_VERTS[i].normal.y;
						vert.normal.z = MESH_GEN_CHUNK_BLOCK_VERTS[i].normal.z;
						meshGeneratorObjectData.push_back(vert);
					}
					for (unsigned int i = 0; i < 36; i++) {
						meshGeneratorObjectElem.push_back(MESH_GEN_CHUNK_BLOCK_ELEMS[i] + count * 24);
					}
					count++;
				}

			}
		}
	}

	return true;
}

void meshGenChunk::setBlocks(blockObject **blocks) {
	if (blocks != nullptr)
		meshGenChunkBlocks = blocks;
}
