cmake_minimum_required(VERSION 3.22)
project(RayTracingTutorial)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracingTutorial main.cpp generals/vec3.h generals/ray.h generals/hittable.h components/hittables/sphere.h components/hittables/hittable_list.h rttutorial.h generals/camera.h generals/material.h components/materials/lambertian.h components/materials/metal.h components/materials/dieletric.h components/components.h generals/ppm_image.h raytracer.h components/hittables/triangle.h components/hittables/moving_sphere.h components/hittables/aabb.h components/hittables/bvh.h generals/texture.h components/textures/solid_texture.h components/textures/checker_texture.h components/perlin.h components/textures/noise_texture.h "external libraries/stb_image.h" components/textures/image_texture.h components/textures/rtt_stb_image.h components/materials/diffuse_light.h components/hittables/aarect.h components/hittables/box.h components/hittables/translate.h components/hittables/rotate.h components/hittables/constant_medium.h components/materials/isotropic.h)
