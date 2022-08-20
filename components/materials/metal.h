#ifndef METAL_H
#define METAL_H

#include "../../generals/material.h"

class metal : public material {
public:

    metal(const color& a, double f) : albedo(make_shared<solid_texture>(a)), fuzz(f < 1 ? f : 1) {}
    explicit metal(shared_ptr<texture> tex, double f) : albedo(std::move(tex)), fuzz(f < 1 ? f : 1)  {}


    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere(), r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return (dot(scattered.direction(), rec.normal) > 0);
    }


public:
    shared_ptr<texture> albedo;
    double fuzz;
};

#endif //METAL_H
