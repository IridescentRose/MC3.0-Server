/*****************************************************************//**
 * \file   ServerBoundProtocol.h
 * \brief  Server Bound Packet Names & Structs
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/
#pragma once
#include "../Types.h"
#include <string>

enum class sbPacketName {
	Disconnect = 0x00,

	Handshake = 0xFF,
};

/**
 * Server-Bound Disconnect.
 * 
 * No fields - causes immediate disconnection.
 */
struct SbDisconnect {};

/**
 * Server-Bound Handshake
 * 
 * Sends protocol ID,
 * Sends username for server information,
 * Sends a UUID for the server to use as player ID
 */
struct SbHandshake{
	u8 protocolID;
	std::string username;
	UUID uuid;
};