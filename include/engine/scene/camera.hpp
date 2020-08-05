#ifndef INCLUDE_ENGINE_SCENE_CAMERA_HPP_
#define INCLUDE_ENGINE_SCENE_CAMERA_HPP_

#include "engine/object/objectGeneric.hpp"
#include <glm/glm.hpp>

class cameraObject: public objectGeneric {
protected:
	glm::vec3 cameraObjectPos;
	glm::vec3 cameraObjectDir;
	glm::vec3 cameraObjectDirRight;
	glm::vec3 cameraObjectDirUp;

	float cameraObjectFov;
	float cameraObjectRatio;
	float cameraObjectPlaneNear;
	float cameraObjectPlaneFar;

	glm::mat4 cameraObjectMatrixView;
	glm::mat4 cameraObjectMatrixProj;
	glm::mat4 cameraObjectMatrix;

public:
	cameraObject();
	virtual ~cameraObject();

	void setPos(glm::vec3 position);
	void setDir(glm::vec3 direction);
	void setFov(float fov);
	void setRatio(float ratio);
	void setPlaneNear(float distance);
	void setPlaneFar(float distance);
	void update();

	glm::vec3 getPos();
	glm::vec3 getDir();
	glm::vec3 getDirRight();
	glm::vec3 getDirUp();
	float getFov();
	float getRatio();
	float getPlaneNear();
	float getPlaneFar();
	glm::mat4 getMatrixView();
	glm::mat4 getMatrixProj();
	glm::mat4 getMatrixPV();
};

#endif
