#pragma once
#include "Client.h"
#include "net/NetworkDriver.h"
#include "net/Socket.h"
#include "Types.h"
#include "util/NonCopy.h"
#include "util/NonMove.h"
#include <vector>

using namespace Stardust;

class Server : public NonCopyable, NonMovable {
	Network::ServerSocket* socket;
	std::vector<Client*> clients;
	bool running;

	void collectDead();
public:
	Server(u16 port);
	~Server();
	void listen();

	inline auto isRunning() {
		return running;
	}
};