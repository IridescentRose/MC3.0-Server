#pragma once
#include "Client.h"

Client::Client(Network::Connection* con) : conn(con) {
	connected = true;
}

Client::~Client() {
	conn->Close();
}