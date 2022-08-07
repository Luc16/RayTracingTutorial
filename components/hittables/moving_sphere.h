#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include <utility>

#include "../../generals/hittable.h"
#include "../../rttutorial.h"

class moving_sphere: public hittable {
public:
    moving_sphere() = default;
    moving_sphere(point3 cen0, point3 cen1, double _time0, double _time1, double r, shared_ptr<material> m):
    center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(std::move(m)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double _time0, double _time1, aabb &output_box) const override;

    point3 center(double time) const;

private:
    point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<material> mat_ptr;
};

point3 moving_sphere::center(double time) const {
    return center0 + (center1-center0)*((time-time0)/(time1-time0));
}

bool moving_sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    point3 current_center = center(r.time());
    auto oc = r.origin() - current_center;
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
    vec3 outward_normal = (rec.p - current_center)/radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool moving_sphere::bounding_box(double _time0, double _time1, aabb &output_box) const {
    auto radius_point = point3(radius, radius, radius);

    auto c0 = center(_time0);
    auto c1 = center(_time1);

    auto box0 = aabb(c0 - radius_point,c0 + radius_point);
    auto box1 = aabb(c1 - radius_point,c1 + radius_point);

    output_box = surrounding_box(box0, box1);

    return true;
}

#endif //MOVING_SPHERE_H
