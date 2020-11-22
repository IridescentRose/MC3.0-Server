/*****************************************************************//**
 * \file   World.h
 * \brief  The main world.
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/
#pragma once
#include <thread>
#include "../util/ThreadSafe.h"
#include "WorldTime.h"

/**
 * Holds our world object.
 */
class World {
	std::thread thr;
	bool running;

	//Everything needs to be ThreadSafe!
	ThreadSafe<WorldTime> worldTime;
	
public:
	World();
	~World();

	static auto tickUpdate(World* self) -> void;

};