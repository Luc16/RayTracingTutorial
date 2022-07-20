#ifndef PPM_IMAGE_H
#define PPM_IMAGE_H

#include <fstream>

class ppm_image: public std::ofstream {
public:
    explicit ppm_image(const std::string &file) {
        open(file);
        if (!is_open()) throw std::runtime_error("Could not open file");
    }

    ~ppm_image() override { close(); }

};
#endif //PPM_IMAGE_H
