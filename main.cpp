/*****************************************************************//**
 * \file   main.cpp
 * \brief  The Main File
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/

#include <iostream>
#include <util/Logger.h>

auto main() -> int {
	g_Logger->setCutoff(LogLevel::Trace);
	g_Logger->info("Welcome!");

	return 0;
}