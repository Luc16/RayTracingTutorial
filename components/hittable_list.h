#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "../generals/hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    hittable_list() = default;
    explicit hittable_list(shared_ptr<hittable> obj) { add(obj); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> obj) { objects.push_back(obj); }

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    bool bounding_box(double time0, double time1, aabb &output_box) const override;


    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& obj : objects) {
        if (obj->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool hittable_list::bounding_box(double time0, double time1, aabb &output_box) const {
    if (objects.empty()) return false;
    aabb box;
    bool first_box;


    for (const auto& obj : objects) {
        if (!obj->bounding_box(time0, time1, box)) return false;

        output_box = first_box ? box : surrounding_box(box, output_box);
        first_box = false;

    }

    return true;

}


#endif //HITTABLE_LIST_H
