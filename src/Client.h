#pragma once
#include "net/NetworkDriver.h"
#include "net/Socket.h"
#include "Types.h"
#include <thread>

using namespace Stardust;

class Client {
	Network::Connection* conn;
	bool connected;

	std::thread thr;
public:
	Client(Network::Connection* con);
	~Client();

	inline auto isClosed() -> bool {
		return connected;
	}

	void start();
	static auto run(Client* self) -> void;
};