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

    float a = 50;


    // Object object(
    //     ObjectType::LINES,
    //     {Vec3{0, 0, 0}, Vec3{a, 0, 0}, Vec3{a / 2, -a * float(sqrt(3)) / 2, 0}, Vec3{a / 2, -a * float(sqrt(3)) / 6, a * float(sqrt(6)) / 3}},
    //     {0, 1, 0, 2, 0, 3, 1, 2, 1, 3, 2, 3}
    // );

    Projector projector;

    World& world = projector.getWorld();
    Camera& camera = projector.getCamera();

    world.addObject(object);
    camera.move({0, 0, -100});

    sf::RenderWindow window(sf::VideoMode({camera.getWidth(), camera.getHeight()}), "3D Renderer");

    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);
    sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen())
    {
        window.setMouseCursorVisible(false);
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
            camera.move(-camera.getRight());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.move(camera.getDirection());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            camera.move(camera.getRight());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.move(-camera.getDirection());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            camera.move(camera.getUp());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            camera.move(-camera.getUp());
        }

        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
        sf::Vector2i delta = currentMousePos - center;

        sf::Mouse::setPosition(center, window);

        camera.updateDirection({delta.x, delta.y});

        projector.projectObjects(window);
        // projector.getWorld().getObject(0).rotateX(0.005);
        // projector.getWorld().getObject(0).rotateY(0.005);
        projector.getWorld().getObject(0).rotateZ(0.01);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5ms);

        window.display();
    }

    return 0;
}