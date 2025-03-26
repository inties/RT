//#define _CRT_SECURE_NO_WARNINGS
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
//#include <cstdlib>  // 添加这个头文件用于system()函数
//
//#include <iostream>
//#include "vector.h"
//#include "ray.h"
//#include"sphere.h"
//#include"hitableList.h"
//#include"somemath.h"
//#include"camera.h"
//#include"material.h"
//            
//vec3 ray_color(const ray& r,const hitableList& world) {
//    HitRecord rec;
//    if (world.hit(r, 0, infinity, rec))return 0.5*rec.normal+vec3(0.5,0.5,0.5);
//    
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//}
//
//int main() {
//    const int image_width = 1920;
//    const int image_height = 1080;
//    const int sample_num = 1;
//    // 创建图像缓冲区
//    unsigned char* image_data = new unsigned char[image_width * image_height * 3];
//    hitableList world;
//    vec3 lower_left_corner(-16.0, -9.0, -5.0);
//    vec3 horizontal(32.0, 0.0, 0.0);
//    vec3 vertical(0.0, 18.0, 0.0);
//    vec3 origin(0.0, 0.0, 0.0);
//    Material material_1(0.5, 0.5, vec3(0.8, 0.2, 0.2));
//    Material material_2(0.7, 0.1, vec3(0.8, 0.4, 0.7));
//    Material material_3(0.1, 0.7, vec3(0.1, 0.9, 0.9));
//
//    shared_ptr<Hittable> s1 = make_shared<Sphere>(vec3(1, 0, -2), 0.5, material_1);
//    shared_ptr<Sphere> s2 = make_shared<Sphere>(vec3(2, 2, -5), 0.5, material_2);
//    shared_ptr<Sphere> s3 = make_shared<Sphere>(vec3(1, 2, -7), 1, material_3);
//    shared_ptr<Sphere> s4 = make_shared<Sphere>(vec3(3, 5, -7), 1, material_2);
//    shared_ptr<Sphere> s5 = make_shared<Sphere>(vec3(0, -1000.5, -1), 1000, material_3);
//    world.add(s1);
//    world.add(s2);
//    world.add(s3);
//    world.add(s4);
//    world.add(s5);
//
//
//    camera cam;
//    int index = 0;
//    for (int j = image_height - 1; j >= 0; --j) {
//        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//        for (int i = 0; i < image_width; ++i) {
//            vec3 color(0, 0, 0);
//            for (int s = 0; s < sample_num; s++) {
//
//                double u = (double(i) + random_double()) / image_width;
//                double v = (double(j) + random_double()) / image_height;
//                ray r = cam.get_ray(u, v);
//                color += ray_color(r, world);
//            }
//            color = color / (double)sample_num;
//            image_data[index++] = static_cast<unsigned char>(255.999 * color.x());
//            image_data[index++] = static_cast<unsigned char>(255.999 * color.y());
//            image_data[index++] = static_cast<unsigned char>(255.999 * color.z());
//        }
//    }
//
//    // 保存图像
//    const char* filename = "output.png";
//    stbi_write_png(filename, image_width, image_height, 3, image_data, image_width * 3);
//
//    // 清理内存
//    delete[] image_data;
//
//    std::cerr << "\nDone. Image saved as '" << filename << "'\n";
//
//    // 根据操作系统自动打开图片
//
//    std::string command = "start " + std::string(filename);
//
//
//    int result = system(command.c_str());
//    if (result != 0) {
//        std::cerr << "Warning: Could not automatically open the image. Please open '"
//            << filename << "' manually.\n";
//    }
//
//    return 0;
//}