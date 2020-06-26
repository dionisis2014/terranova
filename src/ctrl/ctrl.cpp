#include "ctrl/ctrl.hpp"
#include "ctrl/global.hpp"

bool ctrl_init_threads() {
	if (!thread_render.exec())
		return false;

	return true;
}

bool ctrl_destroy_threads() {

	thread::ipc::messageSignal *signal = new thread::ipc::messageSignal(thread::ipc::SIGNAL_TYPE_TERM);
	thread_render.ipc_send(signal);
	if (!thread_render.join())
		return false;

	return true;
}
