/*****************************************************************//**
 * \file   main.cpp
 * \brief  The Main File
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/

#include <iostream>
#include <util/Logger.h>
#include <Server.h>

auto main() -> int {
	g_Logger->setCutoff(LogLevel::Trace);
	g_Logger->info("Welcome to the Minecraft PSP 3.0+ Server!");

	Server srv(3375);

	while (srv.isRunning()) {
		srv.listen();
	}


	return 0;
}