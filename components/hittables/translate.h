#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "../../rttutorial.h"
#include "../../generals/hittable.h"

class translate: public hittable {
public:
    translate(shared_ptr<hittable> obj, const point3& displacement): ptr(std::move(obj)), offset(displacement) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;

private:
    point3 offset;
    shared_ptr<hittable> ptr;
};

bool translate::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    ray moved = ray(r.origin() - offset, r.direction(), r.time());

    if (!ptr->hit(moved, t_min, t_max, rec)) return false;

    rec.p += offset;
    rec.set_face_normal(moved, rec.normal);

    return true;
}

bool translate::bounding_box(double time0, double time1, aabb &output_box) const {
    if (!ptr->bounding_box(time0, time1, output_box)) return false;

    output_box = aabb(output_box.min() + offset, output_box.max() + offset);
    return true;
}

#endif //TRANSLATE_H
