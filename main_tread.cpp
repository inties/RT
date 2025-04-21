#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "hitableList.h"
#include "somemath.h"
#include "camera.h"
#include"mat.h"

vec3 ray_color(const ray& r, const Light& light, const hitableList& world,int& depth) {
    HitRecord rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3(0, 0, 0);

    if (world.hit(r, 0.01, infinity, rec)) {
        vec3 target = rec.position + rec.normal+ random_in_unit_sphere();
        depth -= 1;
        vec3 color_surface;
        ray ray_scatted;
        if (rec.mat_ptr->scatter(r, rec, color_surface, ray_scatted) > 0)
            return  color_surface *ray_color(ray_scatted, light, world, depth);
        else return vec3(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}



void render_region(unsigned char* image_data, Light light, const hitableList& world,
    camera& cam, int image_width, int image_height,
    int sample_num, int start_y, int end_y) {
    for (int j = start_y; j >= end_y; --j) {
        int row_start = (image_height - 1 - j) * image_width * 3;
        for (int i = 0; i < image_width; ++i) {
            int index = row_start + i * 3;
            vec3 color(0, 0, 0);
            for (int s = 0; s < sample_num; s++) {
                double u = (double(i) + random_double()) / image_width;
                double v = (double(j) + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                int depth = 7;
                color += ray_color(r, light, world,depth);
            }
            color = color / (double)sample_num;
            // 检查 color 值
            if (!std::isfinite(color.x()) || !std::isfinite(color.y()) || !std::isfinite(color.z())) {
                /*std::cerr << "Invalid color value at (i=" << i << ", j=" << j << "): "
                    << color.x() << ", " << color.y() << ", " << color.z() << "\n";*/
                color = vec3(1, 0, 0);
            }
            // 检查 index 越界
            if (index < 0 || index + 2 >= image_width * image_height * 3) {
                std::cerr << "Index out of bounds: " << index << " at (i=" << i << ", j=" << j << ")\n";
                std::abort();
            }
            color = vec3(sqrt(color.x()), sqrt(color.y()), sqrt(color.z()));
            image_data[index++] = static_cast<unsigned char>(255.999 * color.x());
            image_data[index++] = static_cast<unsigned char>(255.999 * color.y());
            image_data[index++] = static_cast<unsigned char>(255.999 * color.z());
        }
    }
}
hitableList random_scene() {
    hitableList world;

    world.add(make_shared<Sphere>(
        vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random(0,1) * random(0,1);
                    world.add(
                        make_shared<Sphere>(center, 0.2, make_shared<lambertian>(albedo)));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(.5, 1);
                   /* auto fuzz = random_double(0, .5);*/
                    world.add(
                        make_shared<Sphere>(center, 0.2, make_shared<metal>(albedo)));
                }
                else {
                    // glass
                    world.add(make_shared<Sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    world.add(make_shared<Sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));

    world.add(
        make_shared<Sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

    world.add(
        make_shared<Sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5))));

    return world;
}
int main() {
    const int image_width = 2560;
    const int image_height = 1440;
    const int sample_num = 30;
    const int num_threads = 12;
    const double aspect_ratio = (double)1920 / 1080;
    std::cout << "Using " << num_threads << " threads for rendering.\n";

    unsigned char* image_data = new unsigned char[image_width * image_height * 3];
    if (!image_data) {
        std::cerr << "Failed to allocate image_data\n";
        return 1;
    }

    hitableList world=random_scene();
    Light light{
      vec3(0, 0, 0),   // pos 初始化为 (0,0,0)
       vec3(0, -2, -1),      // dir 初始化为 (1,1,1)
       vec3(1, 1, 0)       // color 初始化为 (1,0,0)，例如红色
    };

 /*   Material material_1(0.5, 0.5, vec3(0.8, 0.2, 0.2));
   

    world.add(make_shared<Sphere>(
        vec3(0, 0, -1), 0.5,  make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));

    world.add(make_shared<Sphere>(
        vec3(0, -100.5, -1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));

    world.add(make_shared<Sphere>(vec3(1, 0, -1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2))));

    world.add(make_shared<Sphere>(vec3(-1, 0, -1), -0.5,  make_shared<dielectric>(1.1)));
    world.add(make_shared<Sphere>(vec3(-2, 1, -1), -0.5,  make_shared<dielectric>(2)));*/

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    std::vector<std::thread> threads;
    int lines_per_thread = image_height / num_threads;

    for (int t = 0; t < num_threads; ++t) {
        int start_y = image_height - 1 - t * lines_per_thread;
        int end_y = (t == num_threads - 1) ? 0 : std::max(0, start_y - lines_per_thread);
        threads.emplace_back(render_region, image_data, light, std::ref(world),
            std::ref(cam), image_width, image_height,
            sample_num, start_y, end_y);
    }

    for (int t = 0; t < num_threads; ++t) {
        threads[t].join();
        std::cerr << "\rThread " << t + 1 << " of " << num_threads << " completed" << std::flush;
    }

    const char* filename = "output.png";
    stbi_write_png(filename, image_width, image_height, 3, image_data, image_width * 3);
    delete[] image_data;

    std::cerr << "\nDone. Image saved as '" << filename << "'\n";
    std::string command = "start " + std::string(filename);
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Warning: Could not automatically open the image. Please open '"
            << filename << "' manually.\n";
    }

    return 0;
}