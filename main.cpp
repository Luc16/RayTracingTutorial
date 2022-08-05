
#include "rttutorial.h"

#include "components/hittable_list.h"
#include "components/materials_and_shapes.h"
#include "generals/camera.h"
#include "raytracer.h"

hittable_list random_scene(point3& out_lookfrom, point3& out_lookat) {
    hittable_list world;

    out_lookfrom = point3(13,2,3);
    out_lookat = point3(0,0,0);

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));

                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                            center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

hittable_list triangle_scene(point3& out_lookfrom, point3& out_lookat) {
    hittable_list world;
    out_lookfrom = point3(0,0,16);
    out_lookat = point3(0,0,-1);

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1,-1000.5), 900, ground_material));
    // triangles
    {
        auto triangle_material1 = make_shared<metal>(color(0.7, 0.6, 0.5), 0);
        auto xs = point3(2.1,2.2,0.8);
        auto ys = point3(0.8,2.2,2.1);
        auto zs = point3(0,2,0);

        auto create_corner_triangle = [triangle_material1](point3 xs, point3 ys, point3 zs) {
            return make_shared<triangle>(
                    point3(xs.x(),ys.x(),zs.x()),
                    point3(xs.y(),ys.y(),zs.y()),
                    point3(xs.z(),ys.z(),zs.z()), triangle_material1
                );
        };
        world.add(create_corner_triangle(-xs, -ys, zs));
        world.add(create_corner_triangle(xs, -ys, zs));
        world.add(create_corner_triangle(-xs, ys, zs));
        world.add(create_corner_triangle(xs, ys, zs));

    }

    //spheres'
    {
        auto sphere_material = make_shared<metal>(color(0.7, 0.8, 0.9), 0.0);
        world.add(make_shared<sphere>(point3(0,0,0), 0.5, sphere_material));
        auto sphere_material2 = make_shared<lambertian>(color(1, 1, 0));
        world.add(make_shared<sphere>(point3(-110,0,110), 100, sphere_material2));

    }

    return world;
}

hittable_list single_ball_scene(point3& out_lookfrom, point3& out_lookat) {
    hittable_list world;

    out_lookfrom = point3(0,0,4);
    out_lookat = point3(0,0,-1);

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    auto center = point3(0, 0, 0);
    auto center2 = center + vec3(0, random_double(0,.8), 0);
    world.add(make_shared<moving_sphere>(
            center, center2, 0.0, 1.0, 0.2, ground_material));

    return world;

};

int main() {

    // Creating/loading the image
    const double aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int samples_per_pixel = 50;
    const int max_depth = 50;

    // Camera

    point3 lookfrom;
    point3 lookat;
    auto world = random_scene(lookfrom, lookat);

    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    raytracer builder("../image.ppm", cam, world, aspect_ratio, image_width, samples_per_pixel, max_depth);

    builder.create_image();
}