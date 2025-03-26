#pragma once
#include"vector.h"
#include"somemath.h"




// ����Ĵֲڶ�ת����������Ҫ����ʵ�֣�
float PerceptualSmoothnessToPerceptualRoughness(float smoothness) {
    return 1.0f - smoothness;  // ��ʾ��ʵ��
}

float PerceptualRoughnessToRoughness(float perceptualRoughness) {
    return perceptualRoughness * perceptualRoughness;  // ��ʾ��ʵ��
}
// ������ʽṹ��
struct Material {

    Material(float metallic, float smoothness, vec3 albedo) :metallic(metallic), smoothness(smoothness), albedo(albedo) {
        getBRDF();
    };
    // BRDF��˫����ֲ��������ṹ��
    struct BRDF {
        vec3 diffuse;    // ��������ɫ
        vec3 specular;   // ���淴����ɫ
        float roughness; // �ֲڶ�
    };
    BRDF brdf;
    float metallic;    // ������
    float smoothness;  // ƽ����
    vec3 albedo;       // �����ʣ�������ɫ��

    // ��ȡBRDF���Եķ���
    BRDF getBRDF() {
          // ����BRDFʵ��

        // ����Ƿ�����
        float oneMinusReflectivity = 1.0f - metallic;

        // ��������ɫ = ������ɫ * �Ƿ�����
        brdf.diffuse = albedo * oneMinusReflectivity;

        // ���㾵�淴����ɫ
        // �ȼ��� albedo �� diffuse �Ĳ�ֵ
        brdf.specular = albedo - brdf.diffuse;
        // ʹ�����Բ�ֵ��Ĭ�Ͼ�����ɫ(0.04)��albedo֮����ݽ����Ȳ�ֵ
        brdf.specular = lerp(vec3(0.04f, 0.04f, 0.04f), albedo, metallic);

        // ����֪ƽ����ת��Ϊ��֪�ֲڶ�
        float perceptualRoughness =
            PerceptualSmoothnessToPerceptualRoughness(smoothness);
        // ����֪�ֲڶ�ת��Ϊʵ�ʴֲڶ�
        brdf.roughness = PerceptualRoughnessToRoughness(perceptualRoughness);

        return brdf;
    }
};
