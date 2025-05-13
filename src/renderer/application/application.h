#include <renderer/world/world.h>
#include <renderer/camera/camera.h>
#include <renderer/projector/projector.h>
#include <SFML/Window.hpp>

class Application
{
public:
  Application();
  void run();

private:
  Projector projector_;
  World world_;
  Camera camera_;
  std::vector<std::vector<sf::Color>> screen_;
  sf::Window view_;

  static const constexpr int cameraWidth_ = 800;
  static const constexpr int cameraHeight_ = 800;
};