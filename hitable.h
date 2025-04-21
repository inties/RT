//hittable.h
#ifndef HITTABLE_H
#define HITTABLE_H
#include"vector.h"
#include"ray.h"
#include"Light.h"
#include"hitrecord.h"
class Hittable;
class material;

class Hittable {
public:
	virtual bool hit(const ray& r, const float min_p, const float max_p, HitRecord& rec)const = 0;
	virtual vec3 color(const ray& r, const Light& light, HitRecord& rec)const = 0;
public:
	shared_ptr<material>mat_ptr;
};





#endif
