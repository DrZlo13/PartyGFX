#include "color.h"

using namespace PartyGFX;

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::operator uint16_t() {
    return (this->r & 0b11111000) << 8 | (this->g & 0b11111100) << 3 | (this->b & 0b11111000) >> 3;
}