#ifndef SPHERE_H
#define SPHERE_H

#include <utility>

#include "../../generals/hittable.h"
#include "../../generals/vec3.h"

class sphere: public hittable {
public:
    sphere() = default;
    sphere(point3 c, double r, shared_ptr<material> m): center(c), radius(r), mat_ptr(std::move(m)) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;


public:
    point3 center;
    double radius{};
    shared_ptr<material> mat_ptr;

private:

    static void get_sphere_uv(const point3& p, double& out_u, double& out_v);
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
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

    return true;

}

bool sphere::bounding_box(double time0, double time1, aabb &output_box) const {
    auto radius_point = point3(radius, radius, radius);
    output_box = aabb(center - radius_point,center + radius_point);

    return true;
}

void sphere::get_sphere_uv(const point3 &p, double &out_u, double &out_v) {
    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;

    out_u = phi/(2*pi);
    out_v = theta/pi;

}

#endif //SPHERE_H
