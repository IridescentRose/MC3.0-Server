#pragma once
#include "Server.h"

Server::Server(u16 port) {
	Network::g_NetworkDriver.Init();

	running = true;
	socket = new Network::ServerSocket(port);
}

Server::~Server() {
	socket->Close();
	delete socket;
	Network::g_NetworkDriver.Cleanup();
}

void Server::collectDead() {
	for (auto i = 0; i < clients.size(); i++) {
		if (clients[i]->isClosed()) {
			delete clients[i];
			clients[i] = nullptr;
		}
	}

	std::vector<Client*> temp;
	for (auto i = 0; i < clients.size(); i++) {
		if (clients[i] != nullptr) {
			temp.push_back(clients[i]);
		}
	}

	clients = temp;
}

void Server::listen() {
	auto conn = socket->ListenState();

	if (conn != nullptr) {
		auto cl = new Client(conn);
		clients.push_back(cl);

		cl->start();
	}

	collectDead();
}