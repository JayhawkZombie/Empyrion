#pragma once

#include <Empyrion/Events/EventAction.h>
#include <SFML/Window.hpp>

#include <vector>

namespace emp
{

  class EventListener
  {
  public:
    EventListener();
    ~EventListener();

    void Update(const sf::Event &Event);
    void Connect(When action);

  private:

    std::vector<When> m_Actions;

  };

}
