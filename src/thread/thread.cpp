#include "thread/thread.hpp"

namespace thread {

thread::thread(function_t function) {
	thread_function = function;
	thread_handle = 0;

	thread_flag_running = false;
}

thread::~thread() {

}

bool thread::exec() {
	if (thread_function == nullptr)
		return false;
	if (thread_flag_running)
		return false;
	if (pthread_self() == thread_handle)
		return false;

	if (pthread_create(&thread_handle, nullptr, thread_function, this))
		return false;
	thread_flag_running = true;

	return true;
}

bool thread::join(void **ret) {
	if (!thread_flag_running)
		return false;
	if (pthread_self() == thread_handle)
		return false;

	if (pthread_join(thread_handle, ret))
		return false;
	thread_flag_running = false;

	return true;
}

bool thread::ipc_recv(ipc::message *&msg) {
	if (pthread_self() == thread_handle)
		return thread_ipc[0].dequeue(msg);
	else
		return thread_ipc[1].dequeue(msg);
}

ipc::queue& thread::ipc_recv() {
	if (pthread_self() == thread_handle)
		return thread_ipc[0];
	else
		return thread_ipc[1];
}

bool thread::ipc_send(ipc::message *msg) {
	if (msg == nullptr)
		return false;

	if (pthread_self() == thread_handle)
		return thread_ipc[1].enqueue(msg);
	else
		return thread_ipc[0].enqueue(msg);
}

ipc::queue& thread::ipc_send() {
	if (pthread_self() == thread_handle)
		return thread_ipc[1];
	else
		return thread_ipc[0];
}

}
