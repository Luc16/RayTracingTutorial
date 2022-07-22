
#include "rttutorial.h"

#include "components/hittable_list.h"
#include "components/sphere.h"
#include "components/materials.h"
#include "generals/camera.h"
#include "raytracer.h"
#include "components/triangle.h"


hittable_list random_scene() {
    hittable_list world;

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

hittable_list simple_scene() {
    hittable_list world;
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000.5,-1), 1000, ground_material));
    auto triangle_material = make_shared<lambertian>(color(1.0, 0.0, 0.0));
    world.add(
            make_shared<triangle>(
                point3(-0.2,-0.25,-2),
                point3(0,0.2,-2),
                point3(0.2,-0.25,-2), triangle_material
            )
    );

    return world;
}

int main() {

    // Creating/loading the image
    const double aspect_ratio = 3.0/2.0;
    const int image_width = 300;
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Creating the world
    auto world = simple_scene();

    // Camera

    point3 lookfrom(0,0,0);
    point3 lookat(0,0,-1);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    raytracer builder("../image.ppm", cam, world, aspect_ratio, image_width, samples_per_pixel, max_depth);

    builder.create_image();
}