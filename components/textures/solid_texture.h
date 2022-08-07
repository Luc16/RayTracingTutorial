#ifndef SOLID_TEXTURE_H
#define SOLID_TEXTURE_H

#include "../../generals/texture.h"

class solid_texture: public texture {
public:

    solid_texture() = default;
    explicit solid_texture(color c): col(c) {}

    solid_texture(double r, double g, double b): col(color(r, g, b)) {}

    color value(double u, double v, const point3 &p) const override { return col; }

private:
    color col;
};

#endif //SOLID_TEXTURE_H
