#include <engine/model/generator/genShpere.hpp>
#include <iostream>
#include "engine/engine.hpp"
#include "engine/shader/shaderManager.hpp"
#include "engine/model/mesh.hpp"
#include "engine/scene/camera.hpp"
#include "engine/scene/scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/world/chunk.hpp"
#include "engine/io/keyboard/keyboard.hpp"

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
	shaderManager.attachAttrib(1, "vertexUv");
	shaderManager.attachAttrib(2, "vertexNormal");
	shaderManager.link();

	shaderManager.attachUniform("matrixPV", UNIFORM_USAGE_MATRIX_PROJVIEW);
	shaderManager.attachUniform("matrixM", UNIFORM_USAGE_MATRIX_MODEL);
	shaderManager.attachUniform("lightAmbient", UNIFORM_USAGE_LIGHT_AMBIENT);
	shaderManager.attachUniform("lightAmbientColor", UNIFORM_USAGE_LIGHT_AMBIENT_COLOR);
	shaderManager.attachUniform("fragmentTexture", UNIFORM_USAGE_TEXTURE);

	shaderManager.use();

	std::cout << "Loading textures ..." << std::endl;
	textureObject to;
	to.load("textures/test.png");
	to.push();

	std::cout << "Pushing model data ..." << std::endl;
	chunkObject co;
	for (int i = 0; i < 16; i++) {
		co.setBlock(new blockObject, i, i, i);
		co.setBlock(new blockObject, i, i, 15 - i);
		co.setBlock(new blockObject, 15 - i, i, 15 - i);
		co.setBlock(new blockObject, 15 - i, i, i);

		co.setBlock(new blockObject, i, 0, 0);
		co.setBlock(new blockObject, i, 0, 15);
		co.setBlock(new blockObject, 0, 0, i);
		co.setBlock(new blockObject, 15, 0, i);
		co.setBlock(new blockObject, 0, i, 0);
		co.setBlock(new blockObject, 15, i, 0);
		co.setBlock(new blockObject, 15, i, 15);
		co.setBlock(new blockObject, 0, i, 15);
		co.setBlock(new blockObject, i, 15, 0);
		co.setBlock(new blockObject, i, 15, 15);
		co.setBlock(new blockObject, 0, 15, i);
		co.setBlock(new blockObject, 15, 15, i);
	}
	co.generateMesh();

	meshObjectIndexed moi;
	moi.push(co.meshVerts(), co.meshElems());

	std::cout << "Setting model attributes ..." << std::endl;
	moi.attribEnable(0);
	moi.attribSet(0, MESH_ATTRIB_FLOAT, 3, 0);
	moi.attribEnable(1);
	moi.attribSet(1, MESH_ATTRIB_FLOAT, 2, (void*) sizeof(meshVertexPos_t));
	moi.attribEnable(2);
	moi.attribSet(2, MESH_ATTRIB_FLOAT, 3, (void*) (sizeof(meshVertexPos_t) + sizeof(meshVertexUv_t)));

	moi.bind();

	std::cout << "Creating scene ..." << std::endl;
	cameraObject cam;
	cam.setPos(glm::vec3(0.0f, 0.0f, 2.0f));
	cam.setDir(-cam.getPos());
	cam.update();

	sceneObject so;
	so.addMesh(&moi, &shaderManager, nullptr);
	so.setLightAmbient(0.1f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float time = 0.0f, timePrev, timeSec = 0.0f;
	float fps = 0.0f;

	while (!glfwWindowShouldClose(engineWindowHandle())) {
		glfwPollEvents();
		if (isKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(engineWindowHandle(), GL_TRUE);

		float speed = 0.1;
		float speedT = 0.05f;
		glm::vec3 stepF = glm::normalize(cam.getDir() * glm::vec3(1.0f, 0.0f, 1.0f)) * speed;
		glm::vec3 stepR = cam.getDirRight() * speed;
		glm::vec3 stepU = glm::vec3(0.0f, 1.0f, 0.0f) * speed;

		if (isKeyPressed(GLFW_KEY_UP))
			cam.setDir(cam.getDir() + cam.getDirUp() * speedT);
		if (isKeyPressed(GLFW_KEY_DOWN))
			cam.setDir(cam.getDir() - cam.getDirUp() * speedT);
		if (isKeyPressed(GLFW_KEY_RIGHT))
			cam.setDir(cam.getDir() + cam.getDirRight() * speedT);
		if (isKeyPressed(GLFW_KEY_LEFT))
			cam.setDir(cam.getDir() - cam.getDirRight() * speedT);

		if (isKeyPressed(GLFW_KEY_W))
			cam.setPos(cam.getPos() + stepF);
		if (isKeyPressed(GLFW_KEY_A))
			cam.setPos(cam.getPos() - stepR);
		if (isKeyPressed(GLFW_KEY_S))
			cam.setPos(cam.getPos() - stepF);
		if (isKeyPressed(GLFW_KEY_D))
			cam.setPos(cam.getPos() + stepR);
		if (isKeyPressed(GLFW_KEY_SPACE))
			cam.setPos(cam.getPos() + stepU);
		if (isKeyPressed(GLFW_KEY_LEFT_SHIFT))
			cam.setPos(cam.getPos() - stepU);

		cam.update();

		timePrev = time;
		time = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		so.render(cam);

		glfwSwapBuffers(engineWindowHandle());

		fps = fps * 59.0f / 60.0f + 1.0f / (time - timePrev) / 60.0f;
		if (time - timeSec > 1.0f) {
			timeSec = time;
			std::string title = "terranova - FPS: ";
			title += std::to_string((int) fps);
			glfwSetWindowTitle(engineWindowHandle(), title.c_str());
		}
	}

	delete[] shaders;

	engineTerm();
	std::cout << "Terminated engine" << std::endl;

	return 0;
}
