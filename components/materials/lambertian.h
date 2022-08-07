#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <utility>

#include "../../generals/material.h"
#include "../textures/solid_texture.h"

class lambertian: public material {
public:

    explicit lambertian(const color& c) : albedo(make_shared<solid_texture>(c)) {}
    explicit lambertian(shared_ptr<texture> tex) : albedo(std::move(tex)) {}


    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

public:
    shared_ptr<texture> albedo;
};

#endif //LAMBERTIAN_H
