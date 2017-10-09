#include <Empyrion/Empyrion.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace emp;

int main(int argc, char **argv)
{
  //iRange tests
  std::cout << "iRange:\n";
  for (auto i : iRange(0, 10)) {
    std::cout << i << ", ";
  } std::cout << "\n";

  std::cout << "iRange_r\n";
  for (auto i : iRange_r(0, 10)) {
    std::cout << i << ", ";
  } std::cout << "\n";

  std::cout << "fRange\n";
  for (auto f : fRange(0.f, 15.f, 3.2f)) {
    std::cout << f << ", ";
  } std::cout << "\n";

  EventListener Listener;
  bool closed = false;

  Listener.Connect(
    When(sf::Event::Closed, [&closed]() { closed = true; })
  );

  sf::RenderWindow Window(sf::VideoMode(800, 800), "Empyrion", sf::Style::Default);

  sf::Texture tex;
  tex.loadFromFile("TestParticle.png");

  ParticleSystem psystem(10000, &tex);

  ParticleEmitter Emitter;
  Emitter.SetEmissionRate(Duration::Milliseconds(1UL));
  Emitter.SetPosition(distributions::Circle(SVector2f(400.f, 680.f), 100.f));
  Emitter.SetRadius([]() { return 20.f; });
  Emitter.SetLifetime(distributions::Duration(2.5, 7.0));

  ParticleEmitter Emitter2;
  Emitter2.SetEmissionRate(Duration::Milliseconds(1UL));
  Emitter2.SetPosition(distributions::Line(SVector2f(600.f, 100.f), SVector2f(600.f, 800.f)));
  Emitter2.SetVelocity(distributions::Radial(0.25f * 3.141592653f, 0.75f * float(3.141592653f), 7.f, 20.f));
  Emitter2.SetRadius([]() { return 12.f; });
  Emitter2.SetLifetime(distributions::Duration(8.0, 8.0));

  psystem.AddAffector(ForceAffector(SVector2f(0.f, -10.f), 2.f));
  psystem.AddAffector(ColorAffector(sf::Color(0, 255, 255), sf::Color(186, 34, 0, 0)));
  psystem.AddAffector(RepulsionAffector(SVector2f(400.f, 330.f), 2.f, 150.f));
  psystem.AddEmitter(Emitter);

  ParticleSystem p2(20000, &tex);

  ParticleEmitter p2e;
  p2e.SetEmissionRate(Duration::Milliseconds(2UL));
  p2e.SetPosition(distributions::Line(SVector2f(15.f, 150.f), SVector2f(250.f, 50.f)));
  //p2e.SetVelocity(distributions::Radial(distributions::Radial(0.25f * 3.141592653f, 0.75f * float(3.141592653f), 7.f, 20.f)));
  p2e.SetRadius([]() { return 15.f; });
  p2e.SetLifetime(distributions::Duration(1.5, 6.0));

  ParticleEmitter p3e;
  p3e.SetEmissionRate(Duration::Milliseconds(2UL));
  p3e.SetPosition(distributions::Line(SVector2f(550.f, 50.f), SVector2f(785.f, 150.f)));
  //p3e.SetVelocity(distributions::Radial(distributions::Radial(0.25f * 3.141592653f, 0.75f * float(3.141592653f), 7.f, 20.f)));
  p3e.SetRadius([]() { return 15.f; });
  p3e.SetLifetime(distributions::Duration(1.5, 6.0));

  //p2.AddAffector(ForceAffector(SVector2f(4.f, -10.f), 3.f));
  p2.AddAffector(ColorAffector(sf::Color(255, 255, 225), sf::Color(114, 0, 42, 0)));
  p2.AddAffector(AttractionAffector(SVector2f(350.f, 150.f), 3.f, 800.f));
  p2.AddAffector(RepulsionAffector(SVector2f(300.f, 55.f), 4.5f, 400.f));
  p2.AddEmitter(p2e);
  p2.AddEmitter(p3e);

  Window.setVerticalSyncEnabled(true);

  while (!closed) {

    sf::Event event;
    while (Window.pollEvent(event))
      Listener.Update(event);

    psystem.Update();
    p2.Update();

    Window.clear(sf::Color::Black);

    psystem.Render(Window);
    p2.Render(Window);

    Window.display();
  }

  Window.close();

  return 0;
}
