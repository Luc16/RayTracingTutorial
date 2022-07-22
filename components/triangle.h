#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>

#include "../generals/hittable.h"
#include "../generals/vec3.h"

class triangle: public hittable {
public:
    triangle() = default;
    triangle(point3 p1, point3 p2, point3 p3, shared_ptr<material> m): mat_ptr(std::move(m)) {
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
    };

    triangle(std::vector<point3> verts, shared_ptr<material> m): vertices(std::move(verts)), mat_ptr(std::move(m)) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


public:
    std::vector<point3> vertices;
    shared_ptr<material> mat_ptr;
};

bool triangle::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {

    vec3 a = vertices[1] - vertices[0];
    vec3 b = vertices[2] - vertices[0];
    vec3 normal = cross(a, b);

    auto denom = normal.dot(r.direction());

    if (fabs(denom) < 1e-5) return false;

    double t = dot(vertices[0] - r.origin(), normal)/denom;

    if (t > t_max || t < t_min) return false;

    auto intersection = r.at(t);

    // translating the vertices so the intersection is the in the origin
    auto tv1 = vertices[0] - intersection;
    auto tv2 = vertices[1] - intersection;
    auto tv3 = vertices[2] - intersection;

    // checking if the triangle contains the origin

    auto u = cross(tv1, tv2);
    auto v = cross(tv2, tv3);
    auto w = cross(tv3, tv1);

    if (u.dot(v) < 0.0 || u.dot(w) < 0.0) return false;

    rec.t = t;
    rec.p = intersection;
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;

}

#endif //TRIANGLE_H
