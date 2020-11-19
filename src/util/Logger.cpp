#include "Logger.h"

ThreadSafe<Logger> g_Logger("log.log");

/**
* Logger instantiation.
*
* \param path - File for the log to output to
* \param name - Name. If omitted - there is no name.
*/
Logger::Logger(const std::string& path, const std::string& name) : cutoff_level(LogLevel::Info), internal_name(name), hasName(name != "") {
	int stat = fopen_s(&internal_file, path.c_str(), "w");

	if (stat != 0) {
		throw std::runtime_error("Could Not Open Log File: " + path);
	}
}

/**
 * Closes the file.
 *
 */
Logger::~Logger() {
	fclose(internal_file);
}