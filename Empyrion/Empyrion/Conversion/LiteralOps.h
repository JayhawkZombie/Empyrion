#pragma once

#include <SFML/Graphics.hpp>

namespace emp
{

  constexpr sf::Uint8 operator""_u8(unsigned long long u) { return static_cast< sf::Uint8 >( u ); }

}
