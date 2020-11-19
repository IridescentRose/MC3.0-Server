#pragma once
#include "NetworkTypes.h"

namespace Stardust::Network {

	/**
	 * Creates a Connection.
	 * Used with a raw connection socket.
	 * Provides us packet methods.
	 */
	class Connection {
	public:
		/**
		 * Constructs a new Connection.
		 * 
		 * \param sock - accepted TCP connection
		 */
		Connection(int sock);

		/**
		 * Destruction.
		 * 
		 */
		~Connection();

		/**
		 * Turns on or off non-blocking mode.
		 * 
		 * \param blocking - True if blocking, false if non-blocking. By default is blocking.
		 * \return - Whether or not operation was successful
		 */
		bool SetBlock(bool blocking);

		/**
		 * Checks if connection is valid.
		 * 
		 * \return - Connection validity.
		 */
		bool isAlive();

		/**
		 * Send a buffer of some sort.
		 * 
		 * \param size - size of data
		 * \param buffer - data buffer
		 */
		void Send(size_t size, char* buffer);

		/**
		 * Packet Receive.
		 * 
		 * \param extended - If we use the u16 ID or u8 ID.
		 * \return - 
		 */
		PacketIn* Recv(bool extended);

		/**
		 * Closes our connection.
		 * Is also done at end of scope if not already done.
		 */
		void Close();

	private:
		int m_socket;
		bool connected;
	};

	/**
	 * Creates a server socket for binding.
	 */
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

		/**
		 * Closes our socket.
		 */
		void Close();

	private:
		int m_socket;
		unsigned short m_PortNo;
	};

}
