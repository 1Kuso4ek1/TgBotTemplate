#pragma once

namespace Env
{

// Environment
inline auto token = std::getenv("TOKEN");

}

namespace Strings
{

inline constexpr auto helloWorld = "Hello World!";

}
