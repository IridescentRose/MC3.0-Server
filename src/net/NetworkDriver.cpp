#include "NetworkDriver.h"
#include <WS2tcpip.h>
#include <util/Logger.h>
#include <stdexcept>

namespace Stardust::Network {

	NetworkDriver::NetworkDriver(){}

	bool NetworkDriver::Init() {
		WSAData data;
		int res = WSAStartup(MAKEWORD(2, 2), &data);
		if (res != 0) {
			throw std::runtime_error("WSAStartup Failed: " + res);
			return false;
		}
	}

	void NetworkDriver::Cleanup() {
	}
}
