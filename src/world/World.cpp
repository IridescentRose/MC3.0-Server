#include "World.h"
#include "../util/Logger.h"

World::World()
{
	thr = std::thread(tickUpdate, this);
	running = true;
}

World::~World() {
	thr.join();
}

auto World::tickUpdate(World* self) -> void {

	while (self->running) {
		self->worldTime->tick();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
