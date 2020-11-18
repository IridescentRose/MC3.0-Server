/*****************************************************************//**
 * \file   logger.ixx
 * \brief  This is the C++20 Module file for Logger. 
 * The package is named Log and includes a very basic file and iostream logger.
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/
#pragma once
#include <fmt/core.h>
#include <stdexcept>
#include "NonCopy.h"
#include "NonMove.h"

/**
 * This exports the Log module.
 */
export module Log;

/**
 * These stages describe the severity of errors within the logger.
 */
export enum class LogLevel {
	Trace,
	Debug,
	Info,
	Warn,
	Error,
};

/**
 * Translates a LogLevel Object into a formatted string.
 * This is module private.
 * 
 * \param level - The Logger Level
 * \return - A string with the name in all capitals.
 */
std::string logLevelToString(const LogLevel& level) {
	switch (level) {
	case LogLevel::Trace:
		return "TRACE";

	case LogLevel::Debug:
		return "DEBUG";

	case LogLevel::Info:
		return "INFO";

	case LogLevel::Warn:
		return "WARN";

	case LogLevel::Error:
		return "ERROR";
	}
}

/**
 * This is the Logger class. It follows RAII patterns and creates a new file on spawn.
 * The Logger can also have a name which prefixes the print.
 * The Logger is not movable nor copyable - it is meant to have a per-class or per-object instance.
 */
export class Logger : public NonCopyable, NonMovable {
	FILE* internal_file;
	LogLevel cutoff_level;

	bool hasName;
	std::string internal_name;

public:

	/**
	 * Logger instantiation.
	 * 
	 * \param path - File for the log to output to
	 * \param name - Name. If omitted - there is no name.
	 */
	Logger(const std::string& path, const std::string& name = ""): cutoff_level(LogLevel::Info), internal_name(name), hasName(name != "") {
		int stat = fopen_s(&internal_file, path.c_str(), "w");

		if (stat != 0) {
			throw std::runtime_error("Could Not Open Log File: " + path);
		}
	}

	/**
	 * Closes the file.
	 * 
	 */
	~Logger() {
		fclose(internal_file);
	}

	/**
	 * Logs a message or discards if below the cutoff level.
	 * 
	 * \param msg - The message you wish to output
	 * \param lvl - The message level 
	 */
	inline auto log(const std::string& msg, const LogLevel& lvl) const {
		if (lvl >= cutoff_level) {
			auto formatStr = (hasName ? "[" + internal_name + "]" : "") + "[" + logLevelToString(lvl) + "]: ";

			fmt::print(formatStr + msg + "\n");
			fmt::print(internal_file, formatStr + msg + "\n");
		}
	}

	/**
	 * Sets the new cutoff level.
	 * 
	 * \param lvl - The new cutoff level
	 */
	inline auto setCutoff(const LogLevel& lvl) {
		cutoff_level = lvl;
	}

	// Simple functions to do a specific level

	inline auto trace(const std::string& msg) const {
		log(msg, LogLevel::Trace);
	}

	inline auto debug(const std::string& msg) const {
		log(msg, LogLevel::Debug);
	}

	inline auto info(const std::string& msg) const {
		log(msg, LogLevel::Info);
	}

	inline auto warn(const std::string& msg) const {
		log(msg, LogLevel::Warn);
	}

	inline auto error(const std::string& msg) const {
		log(msg, LogLevel::Error);
	}
};
