#ifndef INCLUDE_ENGINE_MODEL_GENERATOR_GENSHPERE_HPP_
#define INCLUDE_ENGINE_MODEL_GENERATOR_GENSHPERE_HPP_

#include "engine/model/generator/generator.hpp"

class meshGenSphere : public meshGeneratorObject{
protected:
	unsigned int meshGenSphereResolution;

public:
	meshGenSphere();
	virtual ~meshGenSphere();

	void setResolution(unsigned int resolution);
	bool generate();

	unsigned int getResolution();
};

#endif
