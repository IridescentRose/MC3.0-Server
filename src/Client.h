#pragma once
#include "net/NetworkDriver.h"
#include "net/Socket.h"

using namespace Stardust;

class Client {
	Network::Connection* conn;
	bool connected;
public:
	Client(Network::Connection* con);
	~Client();

	inline auto isClosed() -> bool {
		return connected;
	}
};