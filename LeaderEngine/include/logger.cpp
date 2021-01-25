#include "logger.h"

void Logger::log(const char* msg) {
	std::cout << "[LeaderEngine] " << msg << std::endl;
}