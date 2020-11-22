#pragma once
#include "Client.h"
#include <thread>
#include "util/Logger.h"

Client::Client(Network::Connection* con) : conn(con) {
	connected = true;
}

Client::~Client() {
	conn->Close();
	thr.join();

	delete conn;
}

void Client::start() {
	thr = std::thread(Client::run, this);
}

auto Client::run(Client* self) -> void {
	
	g_Logger->info("Started new thread!");

	//Loop
	while (self->conn->isAlive()) {



		//Sleep for a tick
		std::this_thread::sleep_for(std::chrono::duration<u8, std::milli>(50));
	}

	self->connected = false;
}
