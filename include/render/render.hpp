#ifndef INCLUDE_RENDER_RENDER_HPP_
#define INCLUDE_RENDER_RENDER_HPP_

#include "thread/thread.hpp"

void* render_function(void *ptr);

void render_proc_ipc(thread::thread *t);

#endif
