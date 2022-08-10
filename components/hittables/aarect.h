#ifndef AARECT_H
#define AARECT_H

#include "../../rttutorial.h"
#include "../../generals/hittable.h"

class xy_rect: public hittable{
public:
    xy_rect() = default;

    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> mat):
    x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(std::move(mat)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;


private:
    shared_ptr<material> mp;
    double x0{}, y0{}, x1{}, y1{}, k{};
};

bool xy_rect::bounding_box(double time0, double time1, aabb &output_box) const {
    output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
    return true;
}

bool xy_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    auto t = (k - r.origin().z()) / r.direction().z();

    if (t < t_min || t > t_max) return false;

    point3 p = r.at(t);

    if (p.x() < x0 || p.x() > x1 || p.y() < y0 || p.y() > y1) return false;

    rec.u = (p.x() - x0)/(x1 - x0);
    rec.v = (p.y() - y0)/(y1 - y0);

    auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = p;

    return true;
}

class xz_rect: public hittable{
public:
    xz_rect() = default;

    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<material> mat):
            x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(std::move(mat)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;


private:
    shared_ptr<material> mp;
    double x0{}, z0{}, x1{}, z1{}, k{};
};

bool xz_rect::bounding_box(double time0, double time1, aabb &output_box) const {
    output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
    return true;
}

bool xz_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    auto t = (k - r.origin().y()) / r.direction().y();

    if (t < t_min || t > t_max) return false;

    point3 p = r.at(t);

    if (p.x() < x0 || p.x() > x1 || p.z() < z0 || p.z() > z1) return false;

    rec.u = (p.x() - x0)/(x1 - x0);
    rec.v = (p.z() - z0)/(z1 - z0);

    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = p;

    return true;
}


class yz_rect: public hittable{
public:
    yz_rect() = default;

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<material> mat):
            y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(std::move(mat)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;


private:
    shared_ptr<material> mp;
    double y0{}, z0{}, y1{}, z1{}, k{};
};

bool yz_rect::bounding_box(double time0, double time1, aabb &output_box) const {
    output_box = aabb(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
    return true;
}

bool yz_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    auto t = (k - r.origin().x()) / r.direction().x();

    if (t < t_min || t > t_max) return false;

    point3 p = r.at(t);

    if (p.y() < y0 || p.y() > y1 || p.z() < z0 || p.z() > z1) return false;

    rec.u = (p.y() - y0)/(y1 - y0);
    rec.v = (p.z() - z0)/(z1 - z0);

    auto outward_normal = vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = p;

    return true;
}
#endif //AARECT_H
