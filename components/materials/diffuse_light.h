#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "../../generals/material.h"
#include "../../generals/texture.h"
#include "../textures/solid_texture.h"

class diffuse_light: public material {
public:
    explicit diffuse_light(shared_ptr<texture> a): emit(std::move(a)) {}
    explicit diffuse_light(color c): emit(make_shared<solid_texture>(c)) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        return false;
    }

    color emitted(double u, double v, const point3& p) const override {
        return emit->value(u, v, p);
    }

private:
    shared_ptr<texture> emit;
};

#endif //DIFFUSE_LIGHT_H
