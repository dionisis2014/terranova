#ifndef INCLUDE_ENGINE_MODEL_GENERATOR_GENERATOR_HPP_
#define INCLUDE_ENGINE_MODEL_GENERATOR_GENERATOR_HPP_

#include "engine/object/objectGeneric.hpp"
#include "engine/model/mesh.hpp"

class meshGeneratorObject: public objectGeneric {
protected:
	std::vector<meshVertex_t> meshGeneratorObjectData;
	std::vector<meshVertexElem_t> meshGeneratorObjectElem;
	bool meshGeneratorObjectIndexed;

public:
	meshGeneratorObject();
	virtual ~meshGeneratorObject();

	virtual bool generate() = 0;
	void setIndexed(bool state);

	std::vector<meshVertex_t>& vertices();
	std::vector<meshVertexElem_t>& elements();
	bool getIndexed();
};

#endif
