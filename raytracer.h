#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "generals/vec3.h"
#include "rttutorial.h"
#include "generals/ppm_image.h"
#include "generals/camera.h"
#include "components/hittable_list.h"
#include "components/materials.h"
#include <iostream>

class raytracer {
public:

    raytracer(
            const std::string& imageFile,
            camera& c,
            hittable_list& objs,
            double ap,
            int width,
            int samples_per_pxl,
            int max_depth):
            image(imageFile),
            cam(c),
            world(objs),
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
            std::cout << "\rScanlines remaining: " << j << ", " <<
                      "elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() <<  "s" << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int k = 0; k < samples_per_pixel; k++){
                    auto u = (i + random_double(-1, 1)) / (image_width-1);
                    auto v = (j + random_double(-1, 1)) / (image_height-1);

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

        // Write the translated [0,255] value of each color component.
        image << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }

    color ray_color(const ray& r, int depth){
        hit_record rec;
        if (depth <= 0) return {0, 0, 0};
        if (world.hit(r, 0.001, infinity, rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1);
            return {0, 0, 0};
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5*(unit_direction.y() + 1.0);
        return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
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
};

#endif //RAYTRACER_H
