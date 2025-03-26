#pragma once
//camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "somemath.h"
#include"vector.h"
#include"ray.h"

class camera {
public:
    camera() {
        lower_left_corner = vec3(-16.0, -9.0, -5.0);
        horizontal = vec3(32.0, 0.0, 0.0);
        vertical = vec3(0.0, 18.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    

    ray get_ray(double u, double v)const {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif