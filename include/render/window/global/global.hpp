#ifndef INCLUDE_RENDER_WINDOW_GLOBAL_GLOBAL_HPP_
#define INCLUDE_RENDER_WINDOW_GLOBAL_GLOBAL_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace render {

namespace window {

namespace global {

extern GLFWwindow *window_handle;

extern int window_width;

extern int window_height;

extern int window_antialiasing;

extern std::string window_title;

}

}

}

#endif
