#pragma once
#include <vector>
#include <memory>
#include "element_base.h"
#include "screen_span.h"

namespace PartyGFX {

class Elements {
private:
    std::vector<std::shared_ptr<Element> > elements;

public:
    Elements();
    ~Elements();

    void add_element(std::shared_ptr<Element> element);
    void remove_element(std::shared_ptr<Element> element);
    void render(ScreenSpan& screen);
};

};