#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ctrl/ctrl.hpp"
#include "io/console/logger.hpp"
#include "thread/thread.hpp"
#include "ctrl/global.hpp"
#include "config.hpp"
#include <unistd.h>
#include "io/console/logger.hpp"

int main() {
	io::logger_info << "Starting up ...\n";
	if (!ctrl_init_threads()) {
		io::logger_error << "Error initializing threads!\n";
		return 1;
	}

	thread::ipc::message *msg;
	thread::ipc::messageSignal *signal;
	bool flag_terminate = false;
	bool flag_render_ready = false;

	while (!flag_terminate) {
		while (thread_render.ipc_recv(msg)) {
			switch (msg->msg_type()) {
			case thread::ipc::MESSAGE_TYPE_SIGNAL:
				if ((signal = dynamic_cast<thread::ipc::messageSignal*>(msg))) {
					switch (signal->signal_type()) {
					case thread::ipc::SIGNAL_TYPE_TERM:
						break;
					case thread::ipc::SIGNAL_TYPE_FATALERR:
						io::logger_error << "Renderer reported error! Terminating ...\n";
						flag_terminate = true;
						break;
					case thread::ipc::SIGNAL_TYPE_READY:
						flag_render_ready = true;
						break;
					default:
						break;
					}
				}
				break;
			case thread::ipc::MESSAGE_TYPE_PTR:
				break;
			case thread::ipc::MESSAGE_TYPE_DATA:
				break;
			default:
				break;
			}

			delete msg;
		}

		if (flag_render_ready) {
			glfwPollEvents();
			if (glfwWindowShouldClose(window_handle)) {
				flag_terminate = true;
			}
		}

		usleep(CTRLLOOP_PERIOD);
	}

	io::logger_info << "Shutting down ...\n";
	if (!ctrl_destroy_threads()) {
		io::logger_warn << "Error destroying threads ...\n";
		return 2;
	}

	return 0;
}
