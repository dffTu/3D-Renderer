#include "application.h"
#include <deque>

Application::Application() :
    window_(sf::VideoMode({static_cast<unsigned int>(cameraWidth_), static_cast<unsigned int>(cameraHeight_)}), "3D Renderer"),
    renderer_(),
    world_(),
    camera_(cameraHeight_, cameraWidth_),
    view_(&window_)
{
}

void Application::run()
{
    const int cubes_count = 50;

    std::vector<Object> objects;

    for (size_t i = 0; i < cubes_count; ++i)
    {
        for (size_t j = 0; j < cubes_count; ++j)
        {
            Object obj(
                ObjectType::POLYGONS,
                {Vec3{50, 50, 50}, Vec3{50, -50, 50}, Vec3{-50, -50, 50}, Vec3{-50, 50, 50},
                Vec3{50, 50, -50}, Vec3{50, -50, -50}, Vec3{-50, -50, -50}, Vec3{-50, 50, -50}},
                {0, 1, 2, 0, 2, 3, 0, 1, 5, 0, 5, 4, 2, 3, 6, 3, 7, 6, 4, 5, 6, 4, 6, 7, 0, 3, 4, 3, 4, 7, 1, 2, 5, 2, 5, 6});
            obj.move(Vec3{float(110 * i), float(110 * j), 0});
            obj.setColor(sf::Color::Green);
            objects.push_back(obj);
        }
    }

    for (size_t i = 0; i < objects.size(); ++i)
    {
        world_.addObject(objects[i]);
    }

    sf::Clock clock;
    std::deque<size_t> fpsDeque;

    float cameraVelocity = 600;
    float spinningVelocity = 300;

    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window_);
    sf::Vector2i center(window_.getSize().x / 2, window_.getSize().y / 2);

    sf::Mouse::setPosition(center, window_);

    while (window_.isOpen())
    {
        float timePassed = clock.restart().asSeconds();

        auto now = std::chrono::system_clock::now().time_since_epoch();
        size_t nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

        fpsDeque.push_back(nowMs);
        while (!fpsDeque.empty() && fpsDeque.front() + 1000 < nowMs)
        {
            fpsDeque.pop_front();
        }

        int fps = fpsDeque.size();
        
        handleEvents(timePassed);

        window_.setMouseCursorVisible(false);

        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window_);
        sf::Vector2i delta = currentMousePos - center;

        sf::Mouse::setPosition(center, window_);

        camera_.updateDirection(Vec2{delta.x, delta.y});

        Screen screen = renderer_.projectObjects(world_, camera_);
        view_.show(screen, fps);
        
        for (size_t i = 0; i < objects.size(); ++i)
        {
            // objects[i].rotateX(0.01 * time * spinningVelocity);
            // objects[i].rotateY(0.01 * time * spinningVelocity);
            // objects[i].rotateZ(0.01 * time * spinningVelocity);
            // objects[i].move({0, 0, -float(10) * i * time});
        }
    }
}

void Application::handleEvents(float timePassed)
{
    while (const std::optional event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window_.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window_.close();
        }
    }

    float cameraCoefficient = camera_.getVelocity() * timePassed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        camera_.move(-camera_.getRight() * cameraCoefficient);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        camera_.move(camera_.getDirection() * cameraCoefficient);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        camera_.move(camera_.getRight() * cameraCoefficient);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        camera_.move(-camera_.getDirection() * cameraCoefficient);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        camera_.move(camera_.getUp() * cameraCoefficient);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
        camera_.move(-camera_.getUp() * cameraCoefficient);
    }
}
