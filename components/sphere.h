#ifndef SPHERE_H
#define SPHERE_H

#include <utility>

#include "../generals/hittable.h"
#include "../generals/vec3.h"

class sphere: public hittable {
public:
    sphere() = default;
    sphere(point3 c, double r, shared_ptr<material> m): center(c), radius(r), mat_ptr(std::move(m)) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


public:
    point3 center;
    double radius{};
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    auto oc = r.origin() - center;
    auto a = r.direction_length2();
    auto half_b = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;

    auto delta = half_b*half_b - a*c;

    if (delta < 0) return false;

    auto root = (-half_b - sqrt(delta))/(a);
    if (root > t_max || root < t_min) {
        root = (-half_b + sqrt(delta))/(a);
        if (root > t_max || root < t_min) return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center)/radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;

}

#endif //SPHERE_H
