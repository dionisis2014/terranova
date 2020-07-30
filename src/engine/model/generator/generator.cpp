#include "engine/model/generator/generator.hpp"

meshGeneratorObject::meshGeneratorObject() {
	meshGeneratorObjectIndexed = true;
}

meshGeneratorObject::~meshGeneratorObject() {

}

void meshGeneratorObject::setIndexed(bool state) {
	meshGeneratorObjectIndexed = state;
}

std::vector<meshVertex_t>& meshGeneratorObject::vertices() {
	return meshGeneratorObjectData;
}

std::vector<meshVertexElem_t>& meshGeneratorObject::elements() {
	return meshGeneratorObjectElem;
}

bool meshGeneratorObject::getIndexed() {
	return meshGeneratorObjectIndexed;
}
