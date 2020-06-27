#ifndef INCLUDE_IO_CONSOLE_LOGGER_HPP_
#define INCLUDE_IO_CONSOLE_LOGGER_HPP_

#include <string>
#include <pthread.h>

#define LOGGER_PREFIX_INFO		"[INFO]"
#define LOGGER_PREFIX_WARN		"[WARN]"
#define LOGGER_PREFIX_ERROR		"[ERRO]"

namespace io {

namespace console {

class logger;
extern logger logger_info;
extern logger logger_warn;
extern logger logger_error;

typedef enum {
	LOGGER_NONE,
	LOGGER_INFO,
	LOGGER_WARN,
	LOGGER_ERROR
} logger_type_t;

class logger {
private:
	logger_type_t logger_type;
	bool logger_flag_nl;

	pthread_mutex_t logger_mutex;

public:
	logger(logger_type_t type);
	~logger();

	logger_type_t type();

	logger& operator <<(const char *string);
	logger& operator <<(std::string &string);
};

}

}

#endif
