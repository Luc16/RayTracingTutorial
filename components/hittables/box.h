#ifndef BOX_H
#define BOX_H

#include "../../rttutorial.h"
#include "hittable_list.h"
#include "aarect.h"

class box: public hittable {
public:
    box() = default;

    box(const point3& p_min, const point3& p_max, const shared_ptr<material>& mat_ptr);

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;

private:
    point3 box_max, box_min;
    hittable_list sides;
};

box::box(const point3 &p_min, const point3 &p_max, const shared_ptr<material>& mat_ptr) {
    box_min = p_min;
    box_max = p_max;

    sides.add(make_shared<xy_rect>(p_min.x(), p_max.x(), p_min.y(), p_max.y(), p_max.z(), mat_ptr));
    sides.add(make_shared<xy_rect>(p_min.x(), p_max.x(), p_min.y(), p_max.y(), p_min.z(), mat_ptr));

    sides.add(make_shared<xz_rect>(p_min.x(), p_max.x(), p_min.z(), p_max.z(), p_max.y(), mat_ptr));
    sides.add(make_shared<xz_rect>(p_min.x(), p_max.x(), p_min.z(), p_max.z(), p_min.y(), mat_ptr));

    sides.add(make_shared<yz_rect>(p_min.y(), p_max.y(), p_min.z(), p_max.z(), p_max.x(), mat_ptr));
    sides.add(make_shared<yz_rect>(p_min.y(), p_max.y(), p_min.z(), p_max.z(), p_min.x(), mat_ptr));
}

bool box::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    return sides.hit(r, t_min, t_max, rec);
}

bool box::bounding_box(double time0, double time1, aabb &output_box) const {
    output_box = aabb(box_min, box_max);
    return true;
}

#endif //BOX_H
