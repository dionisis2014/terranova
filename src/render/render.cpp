#include "render/render.hpp"
#include "io/console/logger.hpp"
#include "ctrl/global.hpp"
#include "render/window.hpp"

bool flag_terminate = false;

void* render_function(void *ptr) {
	thread::thread *thread = (thread::thread*) ptr;
	io::logger_info << "Renderer initializing ...\n";

	io::logger_info << "Initializing window ...\n";
	if (!window_init()) {
		io::logger_error << "Failed to initialize window!\n";
		thread::ipc::messageSignal *signal = new thread::ipc::messageSignal(thread::ipc::SIGNAL_TYPE_FATALERR);
		thread->ipc_send(signal);
		flag_terminate = true;
	} else {
		thread::ipc::message *msg = new thread::ipc::messageSignal(thread::ipc::SIGNAL_TYPE_READY);
		thread->ipc_send(msg);
	}

	while (!flag_terminate) {
		render_proc_ipc(thread);

		glfwSwapBuffers(window_handle);
	}

	if (!window_destroy()) {
		io::logger_warn << "Failed to destroy window!\n";
	}

	io::logger_info << "Renderer shutting down ...\n";
	return nullptr;
}

void render_proc_ipc(thread::thread *t) {
	thread::ipc::message *msg;
	thread::ipc::messageSignal *signal;

	while (t->ipc_recv(msg)) {
		switch (msg->msg_type()) {
		case thread::ipc::MESSAGE_TYPE_SIGNAL:
			if ((signal = dynamic_cast<thread::ipc::messageSignal*>(msg))) {
				switch (signal->signal_type()) {
				case thread::ipc::SIGNAL_TYPE_TERM:
					flag_terminate = true;
					break;
				case thread::ipc::SIGNAL_TYPE_FATALERR:
					break;
				case thread::ipc::SIGNAL_TYPE_READY:
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
}
