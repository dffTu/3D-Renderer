#include <renderer/projector/projector.h>
#include <thread>

int main()
{

    Object object(
        ObjectType::LINES,
        {Vec3{50, 50, 50}, Vec3{50, -50, 50}, Vec3{-50, -50, 50}, Vec3{-50, 50, 50},
        Vec3{50, 50, -50}, Vec3{50, -50, -50}, Vec3{-50, -50, -50}, Vec3{-50, 50, -50}},
        {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7}
    );

    Projector projector;

    World& world = projector.getWorld();
    Camera& camera = projector.getCamera();

    world.addObject(object);
    camera.move({0, 0, -100});

    sf::RenderWindow window(sf::VideoMode({camera.getWidth(), camera.getHeight()}), "3D Renderer");

    while (window.isOpen())
    {
        window.clear();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            projector.getCamera().move({-1, 0, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            projector.getCamera().move({0, 0, 1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            projector.getCamera().move({1, 0, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            projector.getCamera().move({0, 0, -1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            projector.getCamera().move({0, 1, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            projector.getCamera().move({0, -1, 0});
        }

        projector.projectObjects(window);
        projector.getWorld().getObject(0).rotateX(0.005);
        projector.getWorld().getObject(0).rotateY(0.005);
        projector.getWorld().getObject(0).rotateZ(0.01);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5ms);

        window.display();
    }

    return 0;
}