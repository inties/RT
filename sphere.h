#ifndef SPHERE
#define SPHERE
#include "hitable.h"
#include "material.h"
#include "Light.h"
#include "somemath.h"
#include <cmath>  // 添加标准数学库支持

class Sphere : public Hittable {
public:
    vec3 center;
    float radius;
    
    //Material material_info;
   

public:
    Sphere(vec3 center, float radius,shared_ptr<material>mat_ptr)
        : center(center), radius(radius) {
        this->mat_ptr = mat_ptr;
    }

    bool hit(const ray& r, const float min_p, const float max_p, HitRecord& rec) const override;
    vec3 color(const ray&r,const Light& light, HitRecord& rec)const override;
};


bool Sphere::hit(const ray& r, const float p_min, const float p_max, HitRecord& rec) const {
    float a = dot(r.direction(), r.direction());
    float half_b = dot(r.direction(), (r.origin() - center));
    float c = dot((r.origin() - center), (r.origin() - center)) - radius * radius;
    float discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;

    float root1 = (-half_b - std::sqrt(discriminant)) / a;
    if (root1 > p_min && root1 < p_max) {
        rec.hittable = this;
        rec.p = root1;
        rec.position = r.at(root1);
        rec.normal = (rec.position - center) / radius;
        rec.set_face_normal(r); // 保证法线始终和入射方向相反
        rec.mat_ptr = this->mat_ptr;
        return true;
    }

    float root2 = (-half_b + std::sqrt(discriminant)) / a;
    if (root2 > p_min && root2 < p_max) {
        rec.hittable = this;
        rec.p = root2;
        rec.position = r.at(root2);
        rec.normal = (rec.position - center) / radius;
        rec.set_face_normal(r); // 保证法线始终和入射方向相反
        rec.mat_ptr = this->mat_ptr;

        return true;
    }
    return false;
}

vec3 Sphere::color(const ray& r, const Light& light, HitRecord& rec)const {
    //vec3 light_reverse = -light.dir;
    //vec3 h = (light_reverse - r.dir) / 2;
    //float nh2 = Square(saturate(dot(rec.normal, h)));      // 使用定义的Square和saturate
    //float lh2 = Square(saturate(dot(light_reverse, h)));       // 使用定义的Square和saturate
    //float r2 = Square(material_info.brdf.roughness);            // 使用定义的Square
    //float d2 = Square(nh2 * (r2 - 1.0f) + 1.00001f);      // 使用定义的Square
    //float normalization = material_info.brdf.roughness * 4.0f + 2.0f;
    //float spec = r2 / (d2 * ffmax(0.1f, lh2) * normalization);
    //vec3 brdfval = material_info.brdf.specular * spec + material_info.brdf.diffuse;
    //return saturate(dot(rec.normal, light_reverse)) * light.color * brdfval;  // 使用定义的saturate
    return vec3(0, 0, 0);
}

#endif