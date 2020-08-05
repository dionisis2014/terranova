#include "engine/scene/scene.hpp"

sceneObject::sceneObject() {
	sceneObjectLightAmbient = 0.5f;
	sceneObjectLightAmbientColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

sceneObject::~sceneObject() {

}

bool sceneObject::addMesh(meshObject *mesh, shaderManager *shadManag, textureObject *texture) {
	if (mesh == nullptr || shadManag == nullptr)
		return false;

	sceneObjectMeshes.push_back(mesh);
	sceneObjectMeshIndexed.push_back(dynamic_cast<meshObjectIndexed*>(mesh) != nullptr);
	sceneObjectShader.push_back(shadManag);
	sceneObjectTextures.push_back(texture);

	return true;
}

bool sceneObject::remMesh(std::size_t index) {
	if (index < 0 || index >= sceneObjectMeshes.size())
		return false;

	sceneObjectMeshes.erase(sceneObjectMeshes.begin() + index);
	sceneObjectMeshIndexed.erase(sceneObjectMeshIndexed.begin() + index);
	sceneObjectShader.erase(sceneObjectShader.begin() + index);

	return true;
}

bool sceneObject::render(cameraObject &camera) {
	if (sceneObjectMeshes.size() == 0)
		return false;

	for (std::size_t i = 0; i < sceneObjectMeshes.size(); i++) {
		if (sceneObjectShader[i]->use()) {
			sceneObjectMeshes[i]->bind();

			//set transforms
			GLint loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_MATRIX_PROJVIEW);
			if (loc == -1) {
				loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_MATRIX_VIEW);
				if (loc == -1)
					return false;
				sceneObjectShader[i]->pushUniformMatrix(loc, camera.getMatrixView());
				loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_MATRIX_PROJECTION);
				if (loc == -1)
					return false;
				sceneObjectShader[i]->pushUniformMatrix(loc, camera.getMatrixProj());
			} else {
				sceneObjectShader[i]->pushUniformMatrix(loc, camera.getMatrixPV());
			}
			loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_MATRIX_MODEL);
			if (loc == -1)
				return false;
			sceneObjectShader[i]->pushUniformMatrix(loc, sceneObjectMeshes[i]->getMatrix());

			//set light
			loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_LIGHT_AMBIENT);
			if (loc >= 0)
				sceneObjectShader[i]->pushUniformF(loc, sceneObjectLightAmbient);

			loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_LIGHT_AMBIENT_COLOR);
			if (loc >= 0)
				sceneObjectShader[i]->pushUniform3F(loc, sceneObjectLightAmbientColor);

			//set texture
			if (sceneObjectTextures[i] != nullptr) {
				glActiveTexture(GL_TEXTURE0);
				sceneObjectTextures[i]->bind();
				loc = sceneObjectShader[i]->getUniform(UNIFORM_USAGE_TEXTURE);
				if (loc >= 0)
					sceneObjectShader[i]->pushUniform1I(loc, 0);
			}

			if (sceneObjectMeshIndexed[i])
				glDrawElements(GL_TRIANGLES, static_cast<meshObjectIndexed*>(sceneObjectMeshes[i])->getElems(), GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(GL_TRIANGLES, 0, sceneObjectMeshes[i]->getVerts());
		}
	}

	return true;
}

void sceneObject::setLightAmbient(float value) {
	sceneObjectLightAmbient = glm::clamp(value, 0.0f, 1.0f);
}

void sceneObject::setLightAmbientColor(glm::vec3 color) {
	sceneObjectLightAmbientColor.x = glm::clamp(color.x, 0.0f, 1.0f);
	sceneObjectLightAmbientColor.y = glm::clamp(color.y, 0.0f, 1.0f);
	sceneObjectLightAmbientColor.z = glm::clamp(color.z, 0.0f, 1.0f);
}

std::vector<meshObject*>& sceneObject::getMeshes() {
	return sceneObjectMeshes;
}

std::vector<shaderManager*>& sceneObject::getShaderes() {
	return sceneObjectShader;
}

std::size_t sceneObject::size() {
	return sceneObjectMeshes.size();
}

float sceneObject::getLightAmbient() {
	return sceneObjectLightAmbient;
}

glm::vec3 sceneObject::getLightAmbientColor() {
	return sceneObjectLightAmbientColor;
}
