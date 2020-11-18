#pragma once
#include "NetworkTypes.h"

namespace Stardust::Network {

	class Connection {
	public:
		Connection(int sock);
		~Connection();

		bool SetBlock(bool blocking);
		bool isAlive();
		void Send(size_t size, char* buffer);
		PacketIn* Recv(bool extended);

		void Close();

	private:
		int m_socket;
		bool connected;
	};

	class ServerSocket {
	public:

		/**
		 * Creates socket and binds it and listens to it.
		 * 
		 * @param port - Port to listen to.
		**/
		ServerSocket(unsigned short port);
		~ServerSocket();

		/**
		 * Listen for a connection
		**/
		Connection* ListenState();

		void Close();

	private:
		int m_socket;
		unsigned short m_PortNo;
	};

}
