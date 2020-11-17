#include <iostream>

import Log;

auto main() -> int {

	auto myLog = Logger("test.log", "Main");

	myLog.log("Test", LogLevel::Info);
	myLog.log("Test", LogLevel::Warn);
	myLog.log("Test", LogLevel::Error);
	myLog.log("Test", LogLevel::Debug);

	return 0;
}