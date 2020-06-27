#include "render/window/window.hpp"
#include "render/window/global/global.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace render {

namespace window {

bool window_init() {
	if (glfwInit() == GLFW_FALSE)
		return false;
	glfwWindowHint(GLFW_SAMPLES, render::window::global::window_antialiasing);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if ((render::window::global::window_handle = glfwCreateWindow(render::window::global::window_width, render::window::global::window_height,
			render::window::global::window_title.c_str(), nullptr, nullptr)) == nullptr) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(render::window::global::window_handle);
	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

bool window_destroy() {
	if (render::window::global::window_handle != nullptr)
		glfwDestroyWindow(render::window::global::window_handle);
	glfwTerminate();

	return true;
}

}

}
