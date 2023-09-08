#include "../element_base.h"

namespace PartyGFX {

class Pixel : public Element {
private:
    Point point;
    Color color;

public:
    Pixel(Point point, Color color);
    ~Pixel();

    void render(ScreenSpan& screen);
    Point get_point();
    void set_point(Point point);
    void set_color(Color color);
};

}