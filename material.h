#pragma once
#include"vector.h"
#include"somemath.h"




// 假设的粗糙度转换函数（需要具体实现）
float PerceptualSmoothnessToPerceptualRoughness(float smoothness) {
    return 1.0f - smoothness;  // 简单示例实现
}

float PerceptualRoughnessToRoughness(float perceptualRoughness) {
    return perceptualRoughness * perceptualRoughness;  // 简单示例实现
}
// 定义材质结构体
struct Material {

    Material(float metallic, float smoothness, vec3 albedo) :metallic(metallic), smoothness(smoothness), albedo(albedo) {
        getBRDF();
    };
    // BRDF（双向反射分布函数）结构体
    struct BRDF {
        vec3 diffuse;    // 漫反射颜色
        vec3 specular;   // 镜面反射颜色
        float roughness; // 粗糙度
    };
    BRDF brdf;
    float metallic;    // 金属度
    float smoothness;  // 平滑度
    vec3 albedo;       // 反照率（基础颜色）

    // 获取BRDF属性的方法
    BRDF getBRDF() {
          // 创建BRDF实例

        // 计算非反射率
        float oneMinusReflectivity = 1.0f - metallic;

        // 漫反射颜色 = 基础颜色 * 非反射率
        brdf.diffuse = albedo * oneMinusReflectivity;

        // 计算镜面反射颜色
        // 先计算 albedo 和 diffuse 的差值
        brdf.specular = albedo - brdf.diffuse;
        // 使用线性插值在默认镜面颜色(0.04)和albedo之间根据金属度插值
        brdf.specular = lerp(vec3(0.04f, 0.04f, 0.04f), albedo, metallic);

        // 将感知平滑度转换为感知粗糙度
        float perceptualRoughness =
            PerceptualSmoothnessToPerceptualRoughness(smoothness);
        // 将感知粗糙度转换为实际粗糙度
        brdf.roughness = PerceptualRoughnessToRoughness(perceptualRoughness);

        return brdf;
    }
};
