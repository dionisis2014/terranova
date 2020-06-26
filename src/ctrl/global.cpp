#include "ctrl/global.hpp"
#include "render/render.hpp"

io::logger_type_t logger_level(io::LOGGER_INFO);

thread::thread thread_render(render_function);

GLFWwindow *window_handle = nullptr;

int window_width = 1280;
int window_height = 720;
int window_antialiasing = 4;
std::string window_title = "Terranova";
