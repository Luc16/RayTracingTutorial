#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction, double time = 0.0): orig(origin), dir(direction), tm(time) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    double time() const { return tm; }
    double direction_length2() const { return dir.length_squared(); }

    point3 at(double t) const { return orig + t*dir; }

private:
    point3 orig;
    vec3 dir;
    double tm;
};

#endif //RAY_H
