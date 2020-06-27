#include "render/global/thread.hpp"
#include "io/console/logger.hpp"
#include "thread/thread.hpp"
#include "render/window/window.hpp"
#include "render/window/global/global.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace render {

namespace global {

bool flag_terminate = false;

void* render_function(void *ptr) {
	thread::thread *thread = (thread::thread*) ptr;
	io::console::logger_info << "Renderer initializing ...\n";

	io::console::logger_info << "Initializing window ...\n";
	if (!render::window::window_init()) {
		io::console::logger_error << "Failed to initialize window!\n";
		thread::ipc::messageSignal *signal = new thread::ipc::messageSignal(thread::ipc::SIGNAL_TYPE_FATALERR);
		thread->ipc_send(signal);
		flag_terminate = true;
	} else {
		thread::ipc::message *msg = new thread::ipc::messageSignal(thread::ipc::SIGNAL_TYPE_READY);
		thread->ipc_send(msg);
	}

	while (!flag_terminate) {
		glfwSwapBuffers(render::window::global::window_handle);
	}

	if (!render::window::window_destroy()) {
		io::console::logger_warn << "Failed to destroy window!\n";
	}

	io::console::logger_info << "Renderer shutting down ...\n";
	return nullptr;
}

}

}
