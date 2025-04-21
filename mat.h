#pragma once
#include"vector.h"
#include"ray.h"
#include"hitrecord.h"

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    double discriminant = 1.0 - r_out_parallel.length_squared();
    if (discriminant < 0) {
        // 全内反射，应该不会到达这里（由 scatter 处理），返回默认值
        return reflect(uv, n); // 或者抛出异常/日志
    }
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}
class material {
public:
    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered
    ) const = 0;
};
//material.h
class lambertian : public material {
public:
    lambertian(const vec3& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered
    ) const {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.position, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    vec3 albedo;
};

class metal :public material {
public:
    metal(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.position, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
public:
    vec3 albedo;

};
double schlick(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
class dielectric :public material {
public:
    dielectric(const float& a) :ref_idx(a) {};
    virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)const {
        attenuation = vec3(1.0, 1.0, 1.0);
        float ln = ffmin(dot(rec.normal, -r_in.dir), 1.0);
        float sin_theta = sqrt(1 - ln * ln);
        double etai_over_etat = (rec.frontFace) ? (1.0 / ref_idx) : (ref_idx);
        if (sin_theta * etai_over_etat > 1 || random_double(0, 1) < schlick(ln, ref_idx)) {
            vec3 reflected = reflect(r_in.dir, rec.normal);
            scattered = ray(rec.position, reflected);
            return true;
        }
        else {
            vec3 refracted = refract(r_in.dir, rec.normal, etai_over_etat);
            scattered = ray(rec.position, refracted);
            return true;

        }

    }

public:
    vec3 albedo;
    double ref_idx;
};
//vec3.h