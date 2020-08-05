#ifndef INCLUDE_ENGINE_SCENE_SCENE_HPP_
#define INCLUDE_ENGINE_SCENE_SCENE_HPP_

#include "engine/object/objectGeneric.hpp"
#include "engine/model/mesh.hpp"
#include "engine/shader/shaderManager.hpp"
#include "engine/scene/camera.hpp"
#include "engine/texture/texture.hpp"

class sceneObject: public objectGeneric {
protected:
	std::vector<meshObject*> sceneObjectMeshes;
	std::vector<bool> sceneObjectMeshIndexed;
	std::vector<shaderManager*> sceneObjectShader;
	std::vector<textureObject*> sceneObjectTextures;

	float sceneObjectLightAmbient;
	glm::vec3 sceneObjectLightAmbientColor;

public:
	sceneObject();
	virtual ~sceneObject();

	bool addMesh(meshObject *mesh, shaderManager *shadManag, textureObject *texture);
	bool remMesh(std::size_t index);
	bool render(cameraObject &camera);
	void setLightAmbient(float value);
	void setLightAmbientColor(glm::vec3 color);

	std::vector<meshObject*>& getMeshes();
	std::vector<shaderManager*>& getShaderes();
	std::size_t size();
	float getLightAmbient();
	glm::vec3 getLightAmbientColor();
};

#endif
