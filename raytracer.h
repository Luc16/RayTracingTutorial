#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "rttutorial.h"
#include "generals/ppm_image.h"
#include "generals/camera.h"
#include "components/components.h"
#include <iostream>

class raytracer {
public:

    raytracer(
            const std::string& imageFile,
            camera& c,
            hittable_list& objs,
            color background_color,
            double ap,
            int width,
            int samples_per_pxl,
            int max_depth):
            image(imageFile),
            cam(c),
            world(objs),
            world_tree(bvh_node(objs, c.time0, c.time1)),
            background(background_color),
            aspect_ratio(ap),
            image_width(width),
            samples_per_pixel(samples_per_pxl),
            max_depth(max_depth),
            image_height(static_cast<int>(image_width / aspect_ratio)) {
    }

    void create_image(){
        image << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        auto begin = std::chrono::steady_clock::now();

        for (int j = image_height-1; j >= 0; --j) {
            std::cout << "\rScanlines remaining: " << j << ", elapsed time: " <<
            std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() <<  "s" << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int k = 0; k < samples_per_pixel; k++){
                    auto u = (i + random_double()) / (image_width-1); // TODO random double so
                    auto v = (j + random_double()) / (image_height-1);

                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, max_depth);
                }
                write_color(pixel_color);
            }
        }

        std::cout << "\nDone.\n";
    }



private:

    void write_color(color pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Divide the color by the number of samples and gamma-correct for gamma=2.0.
        auto scale = 1.0 / samples_per_pixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        // Write the translatesimple_light_scened [0,255] value of each color component.
        image << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }

    color ray_color(const ray& r, int depth){
        if (depth <= 0) return {0, 0, 0};

        hit_record rec;
        if (!world_tree.hit(r, 0.001, infinity, rec)) return background;

        ray scattered;
        color attenuation;
        color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered)) return emitted;

        return emitted + attenuation * ray_color(scattered, depth - 1);
    }

private:
    ppm_image image;
    camera cam;
    const double aspect_ratio;
    const int image_width;
    const int image_height;
    const int samples_per_pixel;
    const int max_depth;
    hittable_list world;
    bvh_node world_tree;
    color background;
};

#endif //RAYTRACER_H
