#ifndef INCLUDE_ENGINE_SCENE_SCENE_HPP_
#define INCLUDE_ENGINE_SCENE_SCENE_HPP_

#include "engine/object/objectGeneric.hpp"
#include "engine/model/mesh.hpp"
#include "engine/shader/shaderManager.hpp"
#include "engine/scene/camera.hpp"

class sceneObject: public objectGeneric {
protected:
	std::vector<meshObject*> sceneObjectMeshes;
	std::vector<bool> sceneObjectMeshIndexed;
	std::vector<shaderManager*> sceneObjectShader;

public:
	sceneObject();
	virtual ~sceneObject();

	bool addMesh(meshObject *mesh, shaderManager* shadManag);
	bool remMesh(std::size_t index);
	bool render(cameraObject &camera);

	std::vector<meshObject*>& getMeshes();
	std::vector<shaderManager*>& getShaderes();
	std::size_t size();
};

#endif
