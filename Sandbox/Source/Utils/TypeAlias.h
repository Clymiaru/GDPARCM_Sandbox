#pragma once
#include <memory>

using Uint = unsigned int;
using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;

template <typename T>
using ScopePtr = std::unique_ptr<T>;
template <typename T, typename ... Args>
constexpr ScopePtr<T> createScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;
template <typename T, typename ... Args>
constexpr SharedPtr<T> createShared(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}