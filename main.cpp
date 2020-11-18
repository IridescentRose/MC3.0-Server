#include <iostream>
#include "src/util/ThreadSafe.h"

import Log;

auto main() -> int {

	ThreadSafe<Logger> myLog("test.log", "Main");

	myLog->setCutoff(LogLevel::Trace);
	myLog->log("Test", LogLevel::Info);
	myLog->log("Test", LogLevel::Warn);
	myLog->log("Test", LogLevel::Error);
	myLog->log("Test", LogLevel::Debug);

	return 0;
}