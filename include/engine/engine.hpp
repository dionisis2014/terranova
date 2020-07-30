#ifndef INCLUDE_ENGINE_ENGINE_HPP_
#define INCLUDE_ENGINE_ENGINE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef GLFWwindow* engineWindow;

bool engineInit();

void engineTerm();

engineWindow engineWindowHandle();

#endif
