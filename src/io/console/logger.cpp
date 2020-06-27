#include "io/console/logger.hpp"
#include <iostream>
#include "global/global.hpp"

namespace io {

namespace console {

logger logger_info(LOGGER_INFO);
logger logger_warn(LOGGER_WARN);
logger logger_error(LOGGER_ERROR);

logger::logger(logger_type_t type) {
	logger_type = type;
	logger_flag_nl = true;
	pthread_mutex_init(&logger_mutex, nullptr);
}

logger::~logger() {
	pthread_mutex_destroy(&logger_mutex);
}

logger_type_t logger::type() {
	return logger_type;
}

logger& logger::operator <<(const char *string) {
	if (logger_type != LOGGER_NONE && logger_type >= logger_level) {
		pthread_mutex_lock(&logger_mutex);
		int i = 0;
		while (string[i] != '\0') {
			if (string[i++] == '\n') {
				logger_flag_nl = true;
				break;
			}
		}
		if (logger_flag_nl) {
			logger_flag_nl = false;
			switch (logger_type) {
			case LOGGER_INFO:
				std::cout << LOGGER_PREFIX_INFO " ";
				break;
			case LOGGER_WARN:
				std::cout << LOGGER_PREFIX_WARN " ";
				break;
			case LOGGER_ERROR:
				std::cout << LOGGER_PREFIX_ERROR " ";
				break;
			default:
				break;
			}
		}
		std::cout << string;
		pthread_mutex_unlock(&logger_mutex);
	}

	return *this;
}

logger& logger::operator <<(std::string &string) {
	return *this << string.c_str();
}

}

}
