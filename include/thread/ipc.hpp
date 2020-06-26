#ifndef INCLUDE_THREAD_IPC_HPP_
#define INCLUDE_THREAD_IPC_HPP_

#include <pthread.h>

#define THREAD_IPC_QUEUE_SIZE		32

namespace thread {

namespace ipc {

typedef enum {
	MESSAGE_TYPE_SIGNAL,
	MESSAGE_TYPE_PTR,
	MESSAGE_TYPE_DATA
} message_type_t;

typedef enum {
	SIGNAL_TYPE_TERM,
	SIGNAL_TYPE_FATALERR,
	SIGNAL_TYPE_READY
} signal_type_t;

class message {
private:
	message_type_t message_type;

public:
	message(message_type_t type);
	virtual ~message();

	message_type_t msg_type();
};

class messageSignal: public message {
private:
	signal_type_t messagesignal_type;

public:
	messageSignal(signal_type_t type);
	~messageSignal();

	signal_type_t signal_type();
};

class queue {
private:
	unsigned int queue_size;
	unsigned int queue_elems;
	unsigned int queue_index_head;
	unsigned int queue_index_tail;

	message **queue_array;
	pthread_mutex_t queue_mutex;
	bool queue_flag_mutex;

public:
	queue(unsigned int size = 0);
	~queue();

	bool enqueue(message *msg);
	bool dequeue(message *&msg);
	bool clear();
	unsigned int size();
	unsigned int elements();
};

}

}

#endif
