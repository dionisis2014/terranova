#include "engine/engine.hpp"
#include <iostream>

static engineWindow window_handle = nullptr;

bool engineInit() {
	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "Failed to initialize engine framework!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window_handle = glfwCreateWindow(1280, 720, "terranova", nullptr, nullptr);
	if (window_handle == nullptr) {
		std::cerr << "Failed to initialize engine window!" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window_handle);
	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

void engineTerm() {
	if (window_handle != nullptr)
		glfwDestroyWindow(window_handle);
	glfwTerminate();
}

engineWindow engineWindowHandle() {
	return window_handle;
}
