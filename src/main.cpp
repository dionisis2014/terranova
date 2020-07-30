#include <engine/model/generator/genShpere.hpp>
#include <iostream>
#include "engine/engine.hpp"
#include "engine/shader/shaderManager.hpp"
#include "engine/model/mesh.hpp"
#include "engine/scene/camera.hpp"
#include "engine/scene/scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/world/chunk.hpp"

int main() {

	if (engineInit()) {
		std::cout << "Initialized engine" << std::endl;
	} else {
		std::cerr << "Failed to initialize engine!" << std::endl;
		return 1;
	}

	shaderObject *shaders = new shaderObject[2];
	std::cout << "Compiling vertex shader ..." << std::endl;
	shaders[0].compile("shaders/basic.vert", SHADER_VERTEX);
	std::cout << "Compiling fragment shader ..." << std::endl;
	shaders[1].compile("shaders/basic.frag", SHADER_FRAGMENT);

	shaderManager shaderManager;
	std::cout << "Attaching shaders and attributes ..." << std::endl;
	shaderManager.attachShader(shaders);
	shaderManager.attachShader(shaders + 1);
	shaderManager.attachAttrib(0, "vertexPosition");
	shaderManager.attachAttrib(1, "vertexColor");
	shaderManager.attachAttrib(2, "vertexNormal");
	shaderManager.link();

	shaderManager.attachUniform("matrixPV", UNIFORM_USAGE_MATRIX_PROJVIEW);
	shaderManager.attachUniform("matrixM", UNIFORM_USAGE_MATRIX_MODEL);
	shaderManager.attachUniform("lightAmbient", UNIFORM_USAGE_LIGHT_AMBIENT);
	shaderManager.attachUniform("lightAmbientColor", UNIFORM_USAGE_LIGHT_AMBIENT_COLOR);

	shaderManager.use();

	std::cout << "Pushing model data ..." << std::endl;
	chunkObject co;
	co.generateMesh();

	meshObjectIndexed moi;
	moi.push(co.meshVerts(), co.meshElems());
	std::cout << "Setting model attributes ..." << std::endl;
	moi.attribEnable(0);
	moi.attribSet(0, MESH_ATTRIB_FLOAT, 3, 0);
	moi.attribEnable(1);
	moi.attribSet(1, MESH_ATTRIB_FLOAT, 3, (void*) sizeof(meshVertexPos_t));
	moi.attribEnable(2);
	moi.attribSet(2, MESH_ATTRIB_FLOAT, 3, (void*) (sizeof(meshVertexPos_t) + sizeof(meshVertexCol_t)));

	moi.bind();

	std::cout << "Creating scene ..." << std::endl;
	cameraObject cam;
	cam.setPos(glm::vec3(10.0f, 10.0f, 10.0f));
	cam.setDir(-cam.getPos());
	cam.update();

	sceneObject so;
	so.addMesh(&moi, &shaderManager);
	so.setLightAmbient(0.1f);

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float angle = 0.0f;
	float time = 0.0f, timePrev, timeSec = 0.0f;
	float fps = 0.0f;
	glm::mat4 original = moi.getMatrix();

	while (!glfwWindowShouldClose(engineWindowHandle())) {
		glfwPollEvents();
		if (glfwGetKey(engineWindowHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(engineWindowHandle(), GL_TRUE);

		angle += glm::radians(360.0f / 60.0f / 5.0f);
		if (angle >= glm::radians(360.0f))
			angle -= glm::radians(360.0f);
		float idk = sin(angle) / 5.0f + 0.75f;
		moi.setMatrix(glm::scale(glm::rotate(original, angle, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(idk, idk, idk)));

		timePrev = time;
		time = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		so.render(cam);

		glfwSwapBuffers(engineWindowHandle());

		fps = fps * 59.0f / 60.0f + 1.0f / (time - timePrev) / 60.0f;
		if (time - timeSec > 1.0f) {
			timeSec = time;
			std::cout << "FPS: " << fps << std::endl;
		}
	}

	delete[] shaders;

	engineTerm();
	std::cout << "Terminated engine" << std::endl;

	return 0;
}
