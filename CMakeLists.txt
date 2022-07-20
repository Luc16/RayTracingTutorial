cmake_minimum_required(VERSION 3.22)
project(RayTracingTutorial)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracingTutorial main.cpp generals/vec3.h generals/color.h generals/ray.h generals/hittable.h components/sphere.h components/hittable_list.h rttutorial.h generals/camera.h generals/material.h components/lambertian.h components/metal.h components/dieletric.h components/materials.h generals/ppm_image.h)
