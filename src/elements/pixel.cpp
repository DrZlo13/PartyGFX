#include "pixel.h"

using namespace PartyGFX;

Pixel::Pixel(Point point, Color color) {
    this->point = point;
    this->color = color;
}

Pixel::~Pixel() {
}

void Pixel::render(ScreenSpan& screen) {
    if(screen.coords.contains(this->point)) {
        screen.set_pixel(this->point, this->color);
    }
}
