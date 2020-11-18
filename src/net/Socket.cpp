#include "Socket.h"
#include <iostream>
#include <zlib/zlib.h>	
#include <util/Logger.h>
#include <WS2tcpip.h>

namespace Stardust::Network {

	ServerSocket::~ServerSocket(){
	
	}

	ServerSocket::ServerSocket(unsigned short port)
	{
		m_socket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));

		if (m_socket == -1) {
			throw std::runtime_error("Fatal: Could not open socket! Errno: " + std::to_string(errno));
		}
		m_PortNo = port;



		g_Logger->debug("Socket Created!");

		sockaddr_in sockaddr;
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = INADDR_ANY;
		sockaddr.sin_port = htons(port);

		if (bind(m_socket, (struct sockaddr*) & sockaddr, sizeof(sockaddr)) < 0) {
			throw std::runtime_error("Fatal: Could not bind socket address! Port: " + std::to_string(port) + ". Errno: " + std::to_string(errno));
		}

		g_Logger->debug("Socket Bound!");
	}

	Connection* ServerSocket::ListenState() {	
		sockaddr_in sockaddr;
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = INADDR_ANY;
		sockaddr.sin_port = htons(m_PortNo);

		g_Logger->debug("Listening on socket...");
		if (listen(m_socket, 1) < 0) {
			throw std::runtime_error("Fatal: Could not listen on socket. Errno: " + std::to_string(errno));
		}

		auto addrlen = sizeof(sockaddr);
		g_Logger->debug("Found potential connection...");

		Connection* conn = new Connection(static_cast<int>(accept(m_socket, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen)));
		g_Logger->info("New Connection from " + std::string((inet_ntoa(sockaddr.sin_addr))) + " on port " + std::to_string(ntohs(sockaddr.sin_port)));

		return conn;
	}

	Connection::Connection(int conn) {
		m_socket = conn;
		if (m_socket < 0) {
			throw std::runtime_error("Fatal: Could not accept connection. Errno: " + std::to_string(errno));
		}
		SetBlock(false);
	}

	void ServerSocket::Close()
	{
		g_Logger->info("Closing connection!");
		closesocket(m_socket);
	}

	void Connection::Close()
	{
		g_Logger->info("Closing connection!");
		closesocket(m_socket);
	}

	bool Connection::SetBlock(bool blocking)
	{
		unsigned long iMode = !blocking;
		int iResult = ioctlsocket(m_socket, FIONBIO, &iMode);
		if (iResult != NO_ERROR) {
			return false;
		}
		return true;
	}

	void Connection::Send(size_t size, char* buffer)
	{
		int res = send(m_socket, buffer, static_cast<int>(size), 0);
		if (res < 0) {
			g_Logger->warn("Failed to send a packet!");
			g_Logger->warn("Packet Size: " + std::to_string(size));
		}
	}

	bool Connection::isAlive()
	{
		bool aconnected = false;
		char buffer[32] = { 0 };
		int res = recv(m_socket, buffer, sizeof(buffer), MSG_PEEK);

		if (res != 0) {
			aconnected = true;
		}
		else {
			Close();
		}

		return aconnected && connected;
	}

	PacketIn* Connection::Recv(bool extended)
	{

		std::vector<byte> len;
		byte newByte;
		int res = recv(m_socket, &newByte, 1, MSG_PEEK);

		if (res > 0) {
			char data[5] = { 0 };
			size_t dataLen = 0;
			do {
				size_t totalReceived = 0;
				while (1 > totalReceived) {
					size_t received = recv(m_socket, &data[dataLen] + totalReceived, static_cast<int>(1 - totalReceived), 0);
					if (received <= 0) {
						std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1));
					}
					else {
						totalReceived += received;
					}
				}
			} while ((data[dataLen++] & 0x80) != 0);

			int readed = 0;
			int result = 0;
			char read;
			do {
				read = data[readed];
				int value = (read & 0b01111111);
				result |= (value << (7 * readed));
				readed++;
			} while ((read & 0b10000000) != 0);


			int length = result;

			PacketIn* pIn = new PacketIn(length);
			g_Logger->debug("LENGTH: " + std::to_string(length));

			int totalTaken = 0;

			byte* b = new byte[length];
			for (int i = 0; i < length; i++) {
				b[i] = 0;
			}

			while (totalTaken < length) {
				int res = recv(m_socket, b, length, 0);
				if (res > 0) {
					totalTaken += res;
				}
				else {
					std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1));
				}
			}


			for (int i = 0; i < length; i++) {
				pIn->buffer->WriteBEUInt8(b[i]);
			}

			if (pIn != NULL && pIn->buffer->GetUsedSpace() > 0) {
				if (extended) {
					pIn->buffer->ReadBEUInt16(pIn->ID);
				}
				else {
					uint8_t t = 0;
					pIn->buffer->ReadBEUInt8(t);
					pIn->ID = t;
				}
			}
			else {
				pIn->ID = -1;
			}

			g_Logger->debug("Received Packet!");
			g_Logger->debug("Packet ID: " + std::to_string(pIn->ID));

			delete[] b;
			return pIn;
		}
		else {
			return NULL;
		}
	}
}