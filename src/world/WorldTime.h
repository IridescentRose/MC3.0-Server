/*****************************************************************//**
 * \file   WorldTime.h
 * \brief  The basic Time Struct
 * 
 * \author Iridescence - Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * \date   November 2020
 *********************************************************************/
#pragma once
#include "../Types.h"

/**
 * Describes world age and day time.
 */
struct WorldTime {
	u64 age;
	u64 day;

	/**
	 * Starts our world at 0,0.
	 * 
	 */
	WorldTime() {
		age = 0;
		day = 0;
	}

	/**
	 * Starts our world at age a and daytime d.
	 * 
	 * \param a - Age of World
	 * \param d - Daytime
	 */
	WorldTime(u64 a, u64 d) {
		age = a;
		day = d;
	}

	/**
	 * Ticks up by one.
	 * 
	 */
	inline auto tick() -> void {
		age++;
		day = (day + 1) % 24000;
	}

	/**
	 * Sets the day time.
	 * 
	 * \param tick - Our new daytime tick
	 */
	inline auto setDay(u64 tick) -> void {
		day = tick;
	}
};