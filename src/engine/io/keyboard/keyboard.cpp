#include "engine/io/keyboard/keyboard.hpp"
#include "engine/engine.hpp"
#include <GLFW/glfw3.h>

bool isKeyPressed(int key) {
	engineWindow window = engineWindowHandle();
	if (window == nullptr)
		return false;
	return glfwGetKey(engineWindowHandle(), key) == GLFW_PRESS;
}

bool isKeyRelease(int key) {
	engineWindow window = engineWindowHandle();
	if (window == nullptr)
		return false;
	return glfwGetKey(engineWindowHandle(), key) == GLFW_RELEASE;
}

bool isKeyRepeat(int key) {
	engineWindow window = engineWindowHandle();
	if (window == nullptr)
		return false;
	return glfwGetKey(engineWindowHandle(), key) == GLFW_REPEAT;
}
