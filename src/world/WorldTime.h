#pragma once
#include "../Types.h"

struct WorldTime {
	u64 age;
	u64 day;

	WorldTime() {
		age = 0;
		day = 0;
	}

	inline auto tick() -> void {
		age++;
		day = (day + 1) % 24000;
	}

	inline auto setDay(u64 tick) -> void {
		day = tick;
	}
};