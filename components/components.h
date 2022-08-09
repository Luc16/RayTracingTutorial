
#ifndef COMPONENTS_H
#define COMPONENTS_H

//materials
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dieletric.h"
#include "../generals/material.h"
#include "materials/diffuse_light.h"

//hittables
#include "hittables/sphere.h"
#include "hittables/triangle.h"
#include "hittables/moving_sphere.h"
#include "hittables/aabb.h"
#include "hittables/bvh.h"
#include "hittables/aarect.h"

//textures
#include "textures/solid_texture.h"
#include "textures/checker_texture.h"
#include "textures/noise_texture.h"
#include "textures/image_texture.h"


#endif //COMPONENTS_H
