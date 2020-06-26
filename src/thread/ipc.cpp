#include "thread/ipc.hpp"

namespace thread {

namespace ipc {

message::message(message_type_t type) {
	message_type = type;
}

message::~message() {

}

message_type_t message::msg_type() {
	return message_type;
}

messageSignal::messageSignal(signal_type_t type) :
		message(MESSAGE_TYPE_SIGNAL) {
	messagesignal_type = type;
}

messageSignal::~messageSignal() {

}

signal_type_t messageSignal::signal_type() {
	return messagesignal_type;
}

queue::queue(unsigned int size) {
	if (size)
		queue_size = size;
	else
		queue_size = THREAD_IPC_QUEUE_SIZE;
	queue_elems = 0;
	queue_index_head = 0;
	queue_index_tail = 0;

	queue_array = new message*[queue_size];
	queue_flag_mutex = pthread_mutex_init(&queue_mutex, nullptr);
}

queue::~queue() {
	if (!queue_flag_mutex)
		pthread_mutex_destroy(&queue_mutex);
	clear();
	if (queue_array != nullptr)
		delete[] queue_array;
}

bool queue::enqueue(message *msg) {
	if (msg == nullptr)
		return false;
	if (queue_array == nullptr)
		return false;
	if (queue_flag_mutex)
		return false;
	if (queue_elems >= queue_size)
		return false;

	if (pthread_mutex_lock(&queue_mutex))
		return false;
	queue_array[queue_index_head++] = msg;
	queue_index_head %= queue_size;
	queue_elems++;
	if (pthread_mutex_unlock(&queue_mutex))
		return false;

	return true;
}

bool queue::dequeue(message *&msg) {
	if (queue_array == nullptr)
		return false;
	if (queue_flag_mutex)
		return false;
	if (queue_elems <= 0)
		return false;

	if (pthread_mutex_lock(&queue_mutex))
		return false;
	msg = queue_array[queue_index_tail++];
	queue_index_tail %= queue_size;
	queue_elems--;
	if (pthread_mutex_unlock(&queue_mutex))
		return false;

	return true;
}

bool queue::clear() {
	if (queue_array == nullptr)
		return false;
	if (queue_flag_mutex)
		return false;

	if (pthread_mutex_lock(&queue_mutex))
		return false;
	while (queue_elems > 0) {
		delete queue_array[queue_index_tail++];
		queue_index_tail %= queue_size;
		queue_elems--;
	}
	queue_index_tail = queue_index_head = 0;
	if (pthread_mutex_unlock(&queue_mutex))
		return false;

	return true;
}

unsigned int queue::size() {
	return queue_size;
}

unsigned int queue::elements() {
	return queue_elems;
}

}

}
