#pragma once
#include <cstdint>

namespace PartyGFX {
class Color {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);
    operator uint16_t();
};
};