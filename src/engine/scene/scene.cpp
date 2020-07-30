#include "engine/scene/scene.hpp"

sceneObject::sceneObject() {

}

sceneObject::~sceneObject() {

}

bool sceneObject::addMesh(meshObject *mesh, shaderManager *shadManag) {
	if (mesh == nullptr || shadManag == nullptr)
		return false;

	sceneObjectMeshes.push_back(mesh);
	sceneObjectMeshIndexed.push_back(dynamic_cast<meshObjectIndexed*>(mesh) != nullptr);
	sceneObjectShader.push_back(shadManag);

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

			if (sceneObjectMeshIndexed[i])
				glDrawElements(GL_TRIANGLES, static_cast<meshObjectIndexed*>(sceneObjectMeshes[i])->getElems(), GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(GL_TRIANGLES, 0, sceneObjectMeshes[i]->getVerts());
		}
	}

	return true;
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
