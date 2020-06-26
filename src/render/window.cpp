#include "render/window.hpp"
#include "ctrl/global.hpp"

bool window_init() {
	if (glfwInit() == GLFW_FALSE)
		return false;
	glfwWindowHint(GLFW_SAMPLES, window_antialiasing);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if ((window_handle = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr)) == nullptr) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window_handle);
	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

bool window_destroy() {
	if (window_handle != nullptr)
		glfwDestroyWindow(window_handle);
	glfwTerminate();

	return true;
}
