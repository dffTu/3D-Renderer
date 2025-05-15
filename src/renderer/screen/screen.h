#pragma once

#include <SFML/Graphics.hpp>

namespace renderer
{

class Screen
{
public:
    using TColor = sf::Color;

    Screen(const int32_t height, const int32_t width);
    void setPixel(const int32_t x, const int32_t y, const TColor& color);
    const TColor& getColor(const int32_t x, const int32_t y) const;

    const int32_t height;
    const int32_t width;

private:
    std::vector<TColor> colors_;
};

}
