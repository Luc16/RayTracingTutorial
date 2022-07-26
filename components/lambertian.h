#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../generals/material.h"

class lambertian: public material {
public:

    explicit lambertian(const color& a) : albedo(a) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};

#endif //LAMBERTIAN_H
