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

//	meshGeneratorObjectData.push_back({0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f});
//	meshGeneratorObjectData.push_back({0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f});
//	meshGeneratorObjectData.push_back({1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f});
//
//	meshGeneratorObjectElem.push_back(0);
//	meshGeneratorObjectElem.push_back(1);
//	meshGeneratorObjectElem.push_back(2);

	unsigned int count = 0;
	for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
		for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
			for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
				for (unsigned int i = 0; i < 24; i++) {
					meshGeneratorObjectData.push_back( {
							{
									MESH_GEN_CHUNK_BLOCK_VERTS[i].position.x + (float) x,
									MESH_GEN_CHUNK_BLOCK_VERTS[i].position.y + (float) y,
									MESH_GEN_CHUNK_BLOCK_VERTS[i].position.z + (float) z
							},
							{
									MESH_GEN_CHUNK_BLOCK_VERTS[i].color.r,
									MESH_GEN_CHUNK_BLOCK_VERTS[i].color.g,
									MESH_GEN_CHUNK_BLOCK_VERTS[i].color.b
							},
							{
									MESH_GEN_CHUNK_BLOCK_VERTS[i].normal.x,
									MESH_GEN_CHUNK_BLOCK_VERTS[i].normal.y,
									MESH_GEN_CHUNK_BLOCK_VERTS[i].normal.z
							}
					});
				}
				for (unsigned int i = 0; i < 36; i++) {
					meshGeneratorObjectElem.push_back(MESH_GEN_CHUNK_BLOCK_ELEMS[i] + count * 36);
				}
				count++;
			}
		}
	}

	return true;
}

void meshGenChunk::setBlocks(blockObject *blocks) {
	if (blocks != nullptr)
		meshGenChunkBlocks = blocks;
}
