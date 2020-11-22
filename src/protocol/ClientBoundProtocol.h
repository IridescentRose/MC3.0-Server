/*****************************************************************//**
 * \file   ClientBoundProtocol.h
 * \brief  Client Bound Packet Names and Structs
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/
#pragma once
#include <string>
#include "../Types.h"

enum class cbPacketName {
	Disconnect = 0x00,

	Handshake = 0xFF,
};

/**
 * Server-Bound Disconnect.
 *
 * No fields - causes immediate disconnection.
 */
struct CbDisconnect {
	std::string reason;
};

/**
 * Client-bound handshake.
 * 
 * This sends the current protocol ID,
 * The server version major,
 * The server version minor,
 * The server version revision.
 */
struct CbHandshake {
	u8 protocolID;
	u8 verMaj;
	u8 verMin;
	u8 verRev;
};