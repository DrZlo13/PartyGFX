#pragma once
#include "screen_span.h"

namespace PartyGFX {
class Element {
public:
    virtual void render(ScreenSpan& screen) = 0;
    virtual ~Element(){};
};
};
