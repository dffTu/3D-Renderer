#pragma once

#include <SFML/Graphics.hpp>
#include <renderer/screen/screen.h>

namespace renderer
{

class View
{
public:
    View(sf::RenderWindow* windowPtr);
    void show(const Screen& screen, const int fps);

private:
    sf::RenderWindow* windowPtr_;
};

}
