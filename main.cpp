
#include "rttutorial.h"

#include "components/components.h"
#include "generals/camera.h"
#include "raytracer.h"

hittable_list random_scene(point3& out_lookfrom, point3& out_lookat, color& out_bg) {
    hittable_list world;

    out_bg = color(0.70, 0.80, 1.00);
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

hittable_list triangle_scene(point3& out_lookfrom, point3& out_lookat, color& out_bg) {
    hittable_list world;
    out_bg = color(0.70, 0.80, 1.00);
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

hittable_list simple_scene(point3& out_lookfrom, point3& out_lookat, color& out_bg) {
    hittable_list world;
    out_bg = color(0.70, 0.80, 1.00);
    out_lookfrom = point3(13,2,3);
    out_lookat = point3(0,0,0);

    auto ground_tex = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 998, make_shared<lambertian>(ground_tex)));

    auto earth_texture = make_shared<image_texture>("../earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);

    auto material3 = make_shared<metal>(earth_texture, 0.0);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, material3);
    world.add(globe);

    return world;

};

hittable_list simple_light_scene(point3& out_lookfrom, point3& out_lookat, color& out_bg) {

    out_bg = color(0.1,0.1,0.1);
    out_lookfrom = point3(26,3,6);
    out_lookat = point3(0,2,0);

    hittable_list objects;

    auto ground_tex = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    objects.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(ground_tex)));
    auto pertext = make_shared<noise_texture>(4);
    objects.add(make_shared<sphere>(point3(-5,2,2), 2, make_shared<lambertian>(pertext)));

    auto earth_texture = make_shared<image_texture>("../earthmap.jpg");
    objects.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(earth_texture)));

    auto difflight = make_shared<diffuse_light>(color(4,4,4));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
    objects.add(make_shared<sphere>(point3(-3,6.5,0), 2, difflight));

    return objects;
}

hittable_list cornell_box(point3& out_lookfrom, point3& out_lookat, color& out_bg) {
    hittable_list objects;

    out_bg = color(0,0,0);
    out_lookfrom = point3(278, 278, -800);
    out_lookat = point3(278, 278, 0);

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15,15,15));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    objects.add(box1);

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));
    objects.add(box2);

    return objects;
}

hittable_list cornell_smoke(point3& out_lookfrom, point3& out_lookat, color& out_bg) {
    hittable_list objects;

    out_bg = color(0,0,0);
    out_lookfrom = point3(278, 278, -800);
    out_lookat = point3(278, 278, 0);

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<hittable> box1 = make_shared<box>(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));

    objects.add(make_shared<constant_medium>(box1, 0.01, color(0,0,0)));
    objects.add(make_shared<constant_medium>(box2, 0.01, color(1,1,1)));

    return objects;
}

hittable_list final_scene(point3& out_lookfrom, point3& out_lookat, color& out_bg) {
    out_bg = color(0,0,0);
    out_lookfrom = point3(478, 278, -600);
    out_lookat = point3(278, 278, 0);

    hittable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<box>(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    hittable_list objects;

    objects.add(make_shared<bvh_node>(boxes1, 0, 1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30,0,0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    objects.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    objects.add(make_shared<sphere>(
            point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<sphere>(point3(360,150,145), 70, make_shared<dielectric>(1.5));
    objects.add(boundary);
    objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
    objects.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("../earthmap.jpg"));
    objects.add(make_shared<sphere>(point3(400,200,400), 100, emat));
    auto pertext = make_shared<noise_texture>(0.1);
    objects.add(make_shared<sphere>(point3(220,280,300), 80, make_shared<lambertian>(pertext)));

    hittable_list boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<sphere>(point3::random(0,165), 10, white));
    }

    objects.add(make_shared<translate>(
                        make_shared<rotate_y>(
                                make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
                        vec3(-100,270,395)
                )
    );

    return objects;
}

int main() {

    // Basic constants
    const double aspect_ratio = 16.0/9.0;
    const int image_width = 600;
    const int samples_per_pixel = 200;
    const int max_depth = 50;
    const int vfov = 20;
//    const double aspect_ratio = 1;
//    const int image_width = 600;
//    const int samples_per_pixel = 200;
//    const int max_depth = 50;
//    const double vfov = 40.0;

    // Camera

    point3 lookfrom;
    point3 lookat;
    color bg;
    auto world = simple_scene(lookfrom, lookat, bg);

    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    raytracer builder(
            "../image.ppm",
            cam,
            world,
            bg,
            aspect_ratio,
            image_width,
            samples_per_pixel,
            max_depth);

    builder.create_image();
}