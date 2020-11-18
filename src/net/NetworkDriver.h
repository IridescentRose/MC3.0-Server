#pragma once
#include "Socket.h"
#include <queue>
#include <map>
#include "NetworkTypes.h"
#include "../util/NonCopy.h"
#include "../util/NonMove.h"

namespace Stardust::Network {
	/**
	 * Handles a specific packet with an ID.
	**/
	typedef int (*PacketHandler)(PacketIn*);

	/**
	 * Basic network interface for Stardust applications.
	**/
	class NetworkDriver : public NonCopyable, NonMovable {
	public:
		
		/**
		 * Default constructor
		**/
		NetworkDriver();

		/**
		 * Starts system-specific network API
		**/
		bool Init();

		/**
		 * Closes system-specific network API
		**/
		void Cleanup();

	};

	extern NetworkDriver g_NetworkDriver;
}
