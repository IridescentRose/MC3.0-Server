#pragma once

/**
 * This makes a class NonMovable.
 * It deletes the functions needed for move construction.
 */
class NonMovable {
public:
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;

protected:
    NonMovable() = default;
};