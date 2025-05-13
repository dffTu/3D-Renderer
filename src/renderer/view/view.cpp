#include "view.h"

View::View(sf::RenderWindow* windowPtr) :
    windowPtr_(windowPtr)
{
}

void View::show(const Screen& screen, const int fps)
{
    windowPtr_->clear();

    sf::Image frameBuffer(
        {
            static_cast<unsigned int>(screen.width),
            static_cast<unsigned int>(screen.height)
        },
        sf::Color::Transparent);
    
    for (int32_t y = 0; y < screen.height; ++y)
    {
        for (int32_t x = 0; x < screen.width; ++x)
        {
            frameBuffer.setPixel({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}, screen.getColor(x, y));
        }
    }

    sf::Texture texture;
    bool _ = texture.loadFromImage(frameBuffer);
    sf::Sprite sprite(texture);
    windowPtr_->draw(sprite);

    sf::Font font("arial.ttf");
    sf::Text text(font);
    text.setString(std::to_string(fps));
    text.setFillColor(sf::Color::Red);
    windowPtr_->draw(text);

    windowPtr_->display();
}
