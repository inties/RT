#pragma once
//rtweekend.h
#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
//rtweekend.h
#include <cstdlib>
#include <functional>
#include <random>
#include"vector.h"
// Usings

using std::shared_ptr;
using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
// Utility Functions

inline double random_double() {
    thread_local std::mt19937 generator(std::random_device{}());
    thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}
inline double random_double(double min, double max) {
    thread_local std::mt19937 generator(std::random_device{}());
    thread_local std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }
// 实现平方函数
inline float Square(float x) {
    return x * x;  // 简单乘法实现平方
}

// 实现饱和函数（限制值在0-1之间）
inline float saturate(float x) {
    return std::fmax(0.0f, std::fmin(1.0f, x));  // 使用标准库函数实现
}


// Common Headers

#endif