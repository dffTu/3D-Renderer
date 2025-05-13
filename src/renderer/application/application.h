#include <renderer/world/world.h>
#include <renderer/camera/camera.h>
#include <renderer/renderer/renderer.h>
#include <renderer/screen/screen.h>
#include <renderer/view/view.h>
#include <SFML/Window.hpp>

class Application
{
public:
    Application();
    void run();

private:
    void handleEvents(float timePassed);

    sf::RenderWindow window_;
    Renderer renderer_;
    World world_;
    Camera camera_;
    View view_;

    static const constexpr int cameraWidth_ = 800;
    static const constexpr int cameraHeight_ = 800;
};
