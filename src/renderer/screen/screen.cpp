#include "screen.h"

namespace renderer
{

Screen::Screen(const int32_t height, const int32_t width) :
    height(height),
    width(width),
    colors_(height * width, TColor::White)
{
}

void Screen::setPixel(const int32_t x, const int32_t y, const TColor& color)
{
    assert(x >= 0 && x < width && y >= 0 && y < height && "Coordinates are incorrect!");

    colors_[y * width + x] = color;
}

const Screen::TColor& Screen::getColor(const int32_t x, const int32_t y) const
{
    assert(x >= 0 && x < width && y >= 0 && y < height && "Coordinates are incorrect!");

    return colors_[y * width + x];
}

}
