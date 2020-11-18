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
	g_Logger->info("Welcome to the Minecraft PSP 3.0+ Server!");



	return 0;
}