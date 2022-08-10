#ifndef ROTATE_H
#define ROTATE_H

#include "../../generals/hittable.h"

class rotate_y: public hittable {
public:
    rotate_y(shared_ptr<hittable> obj, double angle);
    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;

private:
    shared_ptr<hittable> ptr;
    double sin_theta, cos_theta;
    bool hashbox;
    aabb bbox;
};

rotate_y::rotate_y(shared_ptr<hittable> obj, double angle): ptr(std::move(obj)) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);

    hashbox = ptr->bounding_box(0, 1, bbox);

    auto min = point3(infinity, infinity, infinity);
    auto max = point3(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                auto x = i*bbox.max().x() + (1-i)*bbox.min().x();
                auto y = j*bbox.max().y() + (1-j)*bbox.min().y();
                auto z = k*bbox.max().z() + (1-k)*bbox.min().z();

                auto newx =  cos_theta*x + sin_theta*z;
                auto newz = -sin_theta*x + cos_theta*z;

                vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = aabb(min, max);
}

bool rotate_y::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    // reverse rotation
    auto origin = rotate_vec_y(r.origin(), cos_theta,-sin_theta);
    auto direction = rotate_vec_y(r.direction(), cos_theta, -sin_theta);

    auto rotated = ray(origin, direction, r.time());
    if (!ptr->hit(rotated, t_min, t_max, rec)) return false;

    rec.p = rotate_vec_y(rec.p, cos_theta, sin_theta);
    rec.set_face_normal(rotated, rotate_vec_y(rec.normal, cos_theta, sin_theta));

    return true;
}

bool rotate_y::bounding_box(double time0, double time1, aabb &output_box) const {
    output_box = bbox;
    return hashbox;
}

#endif //ROTATE_H
