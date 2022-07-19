#ifndef MATERIAL_H
#define MATERIAL_H

#include "../rttutorial.h"
#include "hittable.h"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;

};

#endif //MATERIAL_H
