#ifndef INCLUDE_CTRL_GLOBAL_HPP_
#define INCLUDE_CTRL_GLOBAL_HPP_

#include "thread/thread.hpp"
#include "io/console/logger.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

extern io::logger_type_t logger_level;

extern thread::thread thread_render;

extern GLFWwindow *window_handle;

extern int window_width;
extern int window_height;
extern int window_antialiasing;
extern std::string window_title;

#endif
