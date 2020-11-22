#pragma once

#include <thread>
#include "../util/ThreadSafe.h"
#include "WorldTime.h"

class World {
	std::thread thr;
	bool running;

	ThreadSafe<WorldTime> worldTime;
	

public:
	World();
	~World();

	static auto tickUpdate(World* self) -> void;


};