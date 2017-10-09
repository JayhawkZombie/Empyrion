#pragma once

#include <SFML/Window.hpp>

#include <map>
#include <functional>

namespace emp
{

  struct When
  {
    When(sf::Event::EventType v, const std::function<void()> &f) : val(v), ftn(f)
    { }

    void operator ()(const sf::Event::EventType &t)
    {
      if (t == val)
        ftn();
    }

    sf::Event::EventType val;
    std::function<void()> ftn = []() { };
  };

}
