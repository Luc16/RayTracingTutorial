#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "../../generals/texture.h"
#include "../perlin.h"

class noise_texture: public texture {
public:

    noise_texture() = default;
    noise_texture(double sc): scale(sc) {}

    color value(double u, double v, const point3 &p) const override {
        return color(1,1,1) * 0.5 * (1 + sin(scale*p.z() + 10*noise.turb(p)));
    }

private:
    double scale;
    perlin noise;

};

#endif //NOISE_TEXTURE_H
