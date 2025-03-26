//#define _CRT_SECURE_NO_WARNINGS
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
//#include <cstdlib>
//#include <iostream>
//#include <thread>
//#include <vector>
//#include <random>
//#include <cmath>
//#include "vector.h"
//#include "ray.h"
//#include "sphere.h"
//#include "hitableList.h"
//#include "somemath.h"
//#include "camera.h"
//
//vec3 ray_color(const ray& r, const Light& light,const hitableList& world) {
//    HitRecord rec;
//    if (world.hit(r, 0, infinity, rec))
//        return rec.hittable->color(r,light,rec);
//
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//}
//
//
//
//void render_region(unsigned char* image_data, Light light,const hitableList& world,
//    const camera& cam, int image_width, int image_height,
//    int sample_num, int start_y, int end_y) {
//    for (int j = start_y; j >= end_y; --j) {
//        int row_start = (image_height - 1 - j) * image_width * 3;
//        for (int i = 0; i < image_width; ++i) {
//            int index = row_start + i * 3;
//            vec3 color(0, 0, 0);
//            for (int s = 0; s < sample_num; s++) {
//                double u = (double(i) + random_double()) / image_width;
//                double v = (double(j) + random_double()) / image_height;
//                ray r = cam.get_ray(u, v);
//                color += ray_color(r,light,world);
//            }
//            color = color / (double)sample_num;
//            // 检查 color 值
//            if (!std::isfinite(color.x()) || !std::isfinite(color.y()) || !std::isfinite(color.z())) {
//                std::cerr << "Invalid color value at (i=" << i << ", j=" << j << "): "
//                    << color.x() << ", " << color.y() << ", " << color.z() << "\n";
//                color = vec3(0, 0, 0);
//            }
//            // 检查 index 越界
//            if (index < 0 || index + 2 >= image_width * image_height * 3) {
//                std::cerr << "Index out of bounds: " << index << " at (i=" << i << ", j=" << j << ")\n";
//                std::abort();
//            }
//            image_data[index++] = static_cast<unsigned char>(255.999 * color.x());
//            image_data[index++] = static_cast<unsigned char>(255.999 * color.y());
//            image_data[index++] = static_cast<unsigned char>(255.999 * color.z());
//        }
//    }
//}
//
//int main() {
//    const int image_width = 1920;
//    const int image_height = 1080;
//    const int sample_num = 10;
//    const int num_threads = 12;
//    std::cout << "Using " << num_threads << " threads for rendering.\n";
//
//    unsigned char* image_data = new unsigned char[image_width * image_height * 3];
//    if (!image_data) {
//        std::cerr << "Failed to allocate image_data\n";
//        return 1;
//    }
//
//    hitableList world;
//    Light light{
//      vec3(0, 0, 0),   // pos 初始化为 (0,0,0)
//       vec3(0, 0, -1),      // dir 初始化为 (1,1,1)
//       vec3(1, 1, 0)       // color 初始化为 (1,0,0)，例如红色
//    }; 
//
//    Material material_1(0.5, 0.5, vec3(0.8, 0.2, 0.2));
//    Material material_2(0.7, 0.1, vec3(0.8, 0.4, 0.7));
//    Material material_3(0.8, 0.7, vec3(0.1, 0.9, 0.9));
//
//    shared_ptr<Hittable> s1 = make_shared<Sphere>(vec3(1, 0, -2), 0.5,material_1);
//    shared_ptr<Sphere> s2 = make_shared<Sphere>(vec3(2, 2, -5),0.5, material_2);
//    shared_ptr<Sphere> s3 = make_shared<Sphere>(vec3(1, 2, -7),1,material_3);
//    shared_ptr<Sphere> s4 = make_shared<Sphere>(vec3(3, 5, -7),1,material_2);
//    shared_ptr<Sphere> s5 = make_shared<Sphere>(vec3(-1, 0, -3),1, material_3);
//    world.add(s1);
//    world.add(s2);
//    world.add(s3);
//    world.add(s4);
//    world.add(s5);
//
//    camera cam;
//
//    std::vector<std::thread> threads;
//    int lines_per_thread = image_height / num_threads;
//
//    for (int t = 0; t < num_threads; ++t) {
//        int start_y = image_height - 1 - t * lines_per_thread;
//        int end_y = (t == num_threads - 1) ? 0 : std::max(0, start_y - lines_per_thread);
//        threads.emplace_back(render_region, image_data, light,std::ref(world),
//            std::ref(cam), image_width, image_height,
//            sample_num, start_y, end_y);
//    }
//
//    for (int t = 0; t < num_threads; ++t) {
//        threads[t].join();
//        std::cerr << "\rThread " << t + 1 << " of " << num_threads << " completed" << std::flush;
//    }
//
//    const char* filename = "output.png";
//    stbi_write_png(filename, image_width, image_height, 3, image_data, image_width * 3);
//    delete[] image_data;
//
//    std::cerr << "\nDone. Image saved as '" << filename << "'\n";
//    std::string command = "start " + std::string(filename);
//    int result = system(command.c_str());
//    if (result != 0) {
//        std::cerr << "Warning: Could not automatically open the image. Please open '"
//            << filename << "' manually.\n";
//    }
//
//    return 0;
//}