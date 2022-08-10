#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "../../generals/material.h"
#include "../../generals/texture.h"
#include "../textures/solid_texture.h"

class isotropic: public material {
public:
    explicit isotropic(color c): albedo(make_shared<solid_texture>(c)) {}
    explicit isotropic(shared_ptr<texture> tex): albedo(std::move(tex)) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }
private:
    shared_ptr<texture> albedo;
};

#endif //ISOTROPIC_H
