#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "../../generals/texture.h"

#include <utility>
#include "solid_texture.h"

class checker_texture: public texture {
public:

    checker_texture() = default;
    checker_texture(color even_col, color odd_col): even(make_shared<solid_texture>(even_col)), odd(make_shared<solid_texture>(odd_col)) {}
    checker_texture(shared_ptr<texture> even_tex, shared_ptr<texture> odd_tex): even(std::move(even_tex)), odd(std::move(odd_tex)) {}

    color value(double u, double v, const point3 &p) const override {
        auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());

        return sines < 0 ? odd->value(u, v, p) : even->value(u, v, p);
    }

private:
    shared_ptr<texture> even, odd;
};


#endif //CHECKER_TEXTURE_H
