#include "application.h"
#include <deque>
#include <iostream>

namespace renderer
{

Application::Application() :
    window_(sf::VideoMode({static_cast<unsigned int>(cameraWidth_), static_cast<unsigned int>(cameraHeight_)}), "3D Renderer"),
    renderer_(),
    world_(),
    camera_(cameraHeight_, cameraWidth_),
    view_(&window_)
{
    world_.addSampleObjects();
}

void Application::run()
{
    sf::Clock clock;
    sf::Vector2i center(window_.getSize().x / 2, window_.getSize().y / 2);
    sf::Mouse::setPosition(center, window_);

    while (window_.isOpen())
    {
        float timePassed = clock.restart().asSeconds();
        
        handleEvents(timePassed);

        window_.setMouseCursorVisible(false);

        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window_);
        sf::Vector2i delta = currentMousePos - center;

        sf::Mouse::setPosition(center, window_);

        camera_.updateDirection(Vec2{delta.x, delta.y});
        world_.animateObjects(timePassed);
        Screen screen = renderer_.projectObjects(world_, camera_);
        view_.show(screen, getFps());
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

int Application::getFps()
{
    auto now = std::chrono::system_clock::now().time_since_epoch();
    size_t nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    fpsDeque_.push_back(nowMs);
    while (!fpsDeque_.empty() && fpsDeque_.front() + 1000 < nowMs)
    {
        fpsDeque_.pop_front();
    }

    return fpsDeque_.size();
}

}
