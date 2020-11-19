#pragma once

/**
 * This makes a class NonCopyable.
 * It removes the Move semantics required for copy construction.
 */
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};