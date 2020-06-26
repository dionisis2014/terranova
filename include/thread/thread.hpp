#ifndef INCLUDE_THREAD_THREAD_HPP_
#define INCLUDE_THREAD_THREAD_HPP_

#include <pthread.h>
#include "thread/ipc.hpp"

namespace thread {

typedef void* (*function_t)(void*);

class thread {
private:
	function_t thread_function;
	pthread_t thread_handle;

	ipc::queue thread_ipc[2];

	bool thread_flag_running;

public:
	thread(function_t function);
	~thread();

	bool exec();
	bool join(void **ret = nullptr);

	bool ipc_recv(ipc::message *&msg);
	ipc::queue& ipc_recv();
	bool ipc_send(ipc::message *msg);
	ipc::queue& ipc_send();
};

}

#endif
