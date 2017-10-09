#include <Empyrion/Events/EventListener.h>

namespace emp
{

  EventListener::EventListener()
  {

  }

  EventListener::~EventListener()
  {

  }

  void EventListener::Update(const sf::Event &Event)
  {
    for (auto & action : m_Actions) {
      action(Event.type);
    }
  }

  void EventListener::Connect(When action)
  {
    m_Actions.emplace_back(action);
  }

}
