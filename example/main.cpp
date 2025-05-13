#include <renderer/application/application.h>

int main()
{
    Application app;
    app.run();
    // Renderer projector;

    // World world;
    // Camera camera(800, 800);

    // const int cubes_count = 50;

    // std::vector<Object> objects;

    // for (size_t i = 0; i < cubes_count; ++i)
    // {
    //     for (size_t j = 0; j < cubes_count; ++j)
    //     {
    //         Object obj(
    //             ObjectType::POLYGONS,
    //             {Vec3{50, 50, 50}, Vec3{50, -50, 50}, Vec3{-50, -50, 50}, Vec3{-50, 50, 50},
    //             Vec3{50, 50, -50}, Vec3{50, -50, -50}, Vec3{-50, -50, -50}, Vec3{-50, 50, -50}},
    //             {0, 1, 2, 0, 2, 3, 0, 1, 5, 0, 5, 4, 2, 3, 6, 3, 7, 6, 4, 5, 6, 4, 6, 7, 0, 3, 4, 3, 4, 7, 1, 2, 5, 2, 5, 6});
    //         obj.move(Vec3{float(110 * i), float(110 * j), 0});
    //         obj.setColor(sf::Color::Green);
    //         objects.push_back(obj);
    //     }
    // }

    // for (size_t i = 0; i < objects.size(); ++i)
    // {
    //     world.addObject(objects[i]);
    // }

    // sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(camera.width), static_cast<unsigned int>(camera.height)}), "3D Renderer");




    // float cameraVelocity = 600;
    // float spinningVelocity = 300;

    // bool showFps = true;
    // std::deque<size_t> fpsDeque;

    // View view(800, 800);

    // sf::RenderWindow& window = view.window();

    // sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);
    // sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);

    // sf::Mouse::setPosition(center, window);

    // sf::Clock clock;

    // while (window.isOpen())
    // {
    //     float time = clock.restart().asSeconds();

    //     auto now = std::chrono::system_clock::now().time_since_epoch();
    //     size_t nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    //     fpsDeque.push_back(nowMs);
    //     while (!fpsDeque.empty() && fpsDeque.front() + 1000 < nowMs)
    //     {
    //         fpsDeque.pop_front();
    //     }

    //     int fps = fpsDeque.size();

    //     if (fps > 2000) fps = 2000;

    //     window.setMouseCursorVisible(false);
    //     window.clear();
    //     while (const std::optional event = window.pollEvent())
    //     {
    //         if (event->is<sf::Event::Closed>())
    //         {
    //             window.close();
    //         }
    //         else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    //         {
    //             if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
    //                 window.close();
    //         }
    //     }

    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    //         camera.move(-camera.getRight() * time * cameraVelocity);
    //     }
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    //         camera.move(camera.getDirection() * time * cameraVelocity);
    //     }
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    //         camera.move(camera.getRight() * time * cameraVelocity);
    //     }
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    //         camera.move(-camera.getDirection() * time * cameraVelocity);
    //     }
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    //         camera.move(camera.getUp() * time * cameraVelocity);
    //     }
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
    //         camera.move(-camera.getUp() * time * cameraVelocity);
    //     }

    //     sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
    //     sf::Vector2i delta = currentMousePos - center;

    //     sf::Mouse::setPosition(center, window);

    //     camera.updateDirection(Vec2{delta.x, delta.y});

    //     Screen screen = projector.projectObjects(world, camera);
    //     view.show(screen);
        
    //     for (size_t i = 0; i < objects.size(); ++i)
    //     {
    //         objects[i].rotateX(0.01 * time * spinningVelocity);
    //         objects[i].rotateY(0.01 * time * spinningVelocity);
    //         objects[i].rotateZ(0.01 * time * spinningVelocity);
    //         objects[i].move({0, 0, -float(10) * i * time});
    //     }

    //     sf::Font font("arial.ttf");
    //     sf::Text text(font);
    //     text.setString(std::to_string(fps));
    //     text.setFillColor(sf::Color::Red);
    //     window.draw(text);

    //     window.display();
    // }

    return 0;
}