#include "engine/scene/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

cameraObject::cameraObject() {
	cameraObjectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraObjectDir = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraObjectDirRight = glm::vec3(1.0f, 0.0f, 0.0f);
	cameraObjectDirUp = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraObjectFov = glm::radians(70.0f);
	cameraObjectRatio = 16.0f / 9.0f;
	cameraObjectPlaneNear = 0.1f;
	cameraObjectPlaneFar = 100.0f;

	cameraObjectMatrixView = glm::mat4(1.0f);
	cameraObjectMatrixProj = glm::mat4(1.0f);
	cameraObjectMatrix = glm::mat4(1.0f);
}

cameraObject::~cameraObject() {

}

void cameraObject::setPos(glm::vec3 position) {
	cameraObjectPos = position;
}

void cameraObject::setDir(glm::vec3 direction) {
	if (direction.length() == 0.0f)
		direction = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraObjectDir = glm::normalize(direction);
	cameraObjectDirRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraObjectDir));
	cameraObjectDirUp = glm::cross(cameraObjectDir, cameraObjectDirRight);
}

void cameraObject::setFov(float fov) {
	cameraObjectFov = fov;
}

void cameraObject::setRatio(float ratio) {
	if (ratio > 0.0f)
		cameraObjectRatio = ratio;
}

void cameraObject::setPlaneNear(float distance) {
	if (distance > 0.0f)
		cameraObjectPlaneNear = distance;
}

void cameraObject::setPlaneFar(float distance) {
	if (distance > 0.0f)
		cameraObjectPlaneFar = distance;
}

void cameraObject::update() {
	cameraObjectMatrixView = glm::lookAt(cameraObjectPos, cameraObjectPos + cameraObjectDir, cameraObjectDirUp);
	cameraObjectMatrixProj = glm::perspective(cameraObjectFov, cameraObjectRatio, cameraObjectPlaneNear, cameraObjectPlaneFar);
	cameraObjectMatrix = cameraObjectMatrixProj * cameraObjectMatrixView;
}

glm::vec3 cameraObject::getPos() {
	return cameraObjectPos;
}

glm::vec3 cameraObject::getDir() {
	return cameraObjectDir;
}

float cameraObject::getFov() {
	return cameraObjectFov;
}

float cameraObject::getRatio() {
	return cameraObjectRatio;
}

float cameraObject::getPlaneNear() {
	return cameraObjectPlaneNear;
}

float cameraObject::getPlaneFar() {
	return cameraObjectPlaneFar;
}

glm::mat4 cameraObject::getMatrixView() {
	return cameraObjectMatrixView;
}

glm::mat4 cameraObject::getMatrixProj() {
	return cameraObjectMatrixProj;
}

glm::mat4 cameraObject::getMatrixPV() {
	return cameraObjectMatrix;
}
