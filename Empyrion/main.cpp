#include <Empyrion/Empyrion.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <ppl.h>
#include <ppltasks.h>

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

  sf::RenderWindow Window(sf::VideoMode(1400, 800), "Empyrion", sf::Style::Default);

  sf::Texture tex;
  tex.loadFromFile("TestParticle.png");

  ParticleSystem psystem(17000, &tex);

  ParticleEmitter Emitter;
  Emitter.SetEmissionRate(Duration::Milliseconds(milliseconds_double(0.5)));
  Emitter.SetPosition(distributions::Circle(SVector2f(700.f, 680.f), 100.f));
  Emitter.SetRadius([]() { return 5.f; });
  Emitter.SetLifetime(distributions::Duration(8.5, 14.0));

  //ParticleEmitter Emitter2;
  //Emitter2.SetEmissionRate(Duration::Milliseconds(1UL));
  //Emitter2.SetPosition(distributions::Line(SVector2f(600.f, 100.f), SVector2f(600.f, 800.f)));
  ////Emitter2.SetVelocity(distributions::Radial(0.25f * 3.141592653f, 0.75f * float(3.141592653f), 7.f, 20.f));
  //Emitter2.SetRadius([]() { return 20.f; });
  //Emitter2.SetLifetime(distributions::Duration(8.0, 8.0));

  psystem.AddAffector(ForceAffector(SVector2f(0.f, -10.f), 1.f));
  psystem.AddAffector(ColorAffector(sf::Color(122, 0, 122), sf::Color(255, 0, 100, 0)));
  psystem.AddAffector(AttractionAffector(SVector2f(400.f, 730.f), 0.4f, 150.f));
  psystem.AddAffector(RepulsionAffector(SVector2f(700.f, 330.f), 1.5f, 350.f));
  psystem.AddAffector(RepulsionAffector(SVector2f(700.f, 730.f), 1.f, 350.f));
  //psystem.AddAffector(AttractionAffector(SVector2f(700.f, 30.f), 0.1f, 150.f));
  psystem.AddAffector(AttractionAffector(SVector2f(1000.f, 730.f), 0.4f, 150.f));
  psystem.AddEmitter(Emitter);

  ParticleSystem p2(10000, &tex);
  ParticleSystem p3(10000, &tex);

  ParticleEmitter p2e;
  p2e.SetEmissionRate(Duration::Milliseconds(1UL));
  p2e.SetPosition(distributions::CircularArea(SVector2f(150.f, 50.f), 100.f));
  //p3e.SetVelocity(distributions::Radial(distributions::Radial(0.25f * 3.141592653f, 0.75f * float(3.141592653f), 7.f, 20.f)));
  p2e.SetRadius([]() { return 15.f; });
  p2e.SetLifetime(distributions::Duration(1.5, 9.0));

  ParticleEmitter p3e;
  p3e.SetEmissionRate(Duration::Milliseconds(1UL));
  p3e.SetPosition(distributions::CircularArea(SVector2f(1150.f, 50.f), 100.f));
  //p3e.SetVelocity(distributions::Radial(distributions::Radial(0.25f * 3.141592653f, 0.75f * float(3.141592653f), 7.f, 20.f)));
  p3e.SetRadius([]() { return 15.f; });
  p3e.SetLifetime(distributions::Duration(1.5, 6.0));

  //p2.AddAffector(ForceAffector(SVector2f(0.f, 10.f), 0.5f));
  p2.AddAffector(ColorAffector(sf::Color(0, 145, 145), sf::Color(114, 0, 42, 0)));
  p2.AddAffector(AttractionAffector(SVector2f(150.f, 350.f), 1.f, 800.f));
  p2.AddAffector(RepulsionAffector(SVector2f(300.f, 759.f), 0.5f, 400.f));
  p2.AddEmitter(p2e);
  //p2.AddEmitter(p3e);
  p3.AddEmitter(p3e);
  p3.AddAffector(ForceAffector(SVector2f(0.f, -10.f), 1.f));
  p3.AddAffector(ColorAffector(sf::Color(122, 0, 122), sf::Color(255, 0, 100, 0)));
  p3.AddAffector(AttractionAffector(SVector2f(400.f, 730.f), 0.4f, 150.f));
  p3.AddAffector(RepulsionAffector(SVector2f(700.f, 330.f), 1.5f, 350.f));
  p3.AddAffector(RepulsionAffector(SVector2f(700.f, 730.f), 1.f, 350.f));
  //psystem.AddAffector(AttractionAffector(SVector2f(700.f, 30.f), 0.1f, 150.f));
  p3.AddAffector(AttractionAffector(SVector2f(1000.f, 730.f), 0.4f, 150.f));

  Window.setVerticalSyncEnabled(false);

  bool running = false;
  Listener.Connect(When(sf::Event::KeyPressed, [&running]() { running = !running; }));

  while (!closed) {

    sf::Event event;
    while (Window.pollEvent(event))
      Listener.Update(event);

    if (running) {
      auto task = concurrency::create_task([&psystem]() { psystem.Update(); });
      auto task2 = concurrency::create_task([&p2]() { p2.Update(); });
      auto task3 = concurrency::create_task([&p3]() { p3.Update(); });

      auto done = task && task2 && task3;
      done.wait();
    //  psystem.Update();
    //p2.Update();
    //p3.Update();
    }
    Window.clear(sf::Color::Black);

    
    psystem.Render(Window);
    p2.Render(Window);
    p3.Render(Window);
    Window.display();
  }

  Window.close();

  return 0;
}
