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

Point PartyGFX::Pixel::get_point() {
    return this->point;
}

void PartyGFX::Pixel::set_point(Point point) {
    this->point = point;
}

void PartyGFX::Pixel::set_color(Color color) {
    this->color = color;
}
