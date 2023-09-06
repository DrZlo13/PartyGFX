#include "elements.h"

using namespace PartyGFX;

Elements::Elements() {
}

Elements::~Elements() {
}

void Elements::add_element(std::shared_ptr<Element> element) {
    this->elements.push_back(element);
}

void Elements::remove_element(std::shared_ptr<Element> element) {
    for(auto it = this->elements.begin(); it != this->elements.end(); it++) {
        if(it->get() == element.get()) {
            this->elements.erase(it);
            return;
        }
    }
}

void Elements::render(ScreenSpan& screen) {
    for(auto it = this->elements.begin(); it != this->elements.end(); it++) {
        it->get()->render(screen);
    }
}