/*****************************************************************//**
 * \file   Client.h
 * \brief  The basic client of the game.
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/
#pragma once
#include "net/NetworkDriver.h"
#include "net/Socket.h"
#include "Types.h"
#include <thread>
#include "util/ThreadSafe.h"
#include <queue>

using namespace Stardust;

class Client {
	Network::Connection* conn;
	ThreadSafe<Network::Connection> safe_conn;
	bool connected;
	bool compression;


	ThreadSafe<std::queue<Network::PacketOut*>> packetQueue;
	ThreadSafe<std::queue<Network::PacketIn*>> receivedQueue;
	std::thread thr;
public:
	/**
	 * New client object.
	 * 
	 * \param con - The connection we have to work with.
	 */
	Client(Network::Connection* con);

	/**
	 * Destroys the client.
	 * 
	 */
	~Client();

	/**
	 * Receives a packet.
	 * 
	 * \return If it was successful or not.
	 */
	auto receivePacket() -> bool;

	/**
	 * Adds a new packet to the queue.
	 * 
	 * \param pack - Packet to send
	 */
	auto addPacket(Network::PacketOut* pack) -> void;

	/**
	 * Sends the packet queue
	 * 
	 */
	auto sendPacket() -> void;

	/**
	 * Handles packets.
	 * 
	 */
	auto handlePackets() -> void;

	/**
	 * Check for if the client is alive.
	 * 
	 * \return - Is the client alive?
	 */
	inline auto isClosed() -> bool {
		return connected;
	}

	/**
	 * Starts a new thread.
	 * 
	 */
	auto start() -> void;

	/**
	 * Our main program loop.
	 *
	 * \param self - The client object
	 */
	static auto run(Client* self) -> void;
};