//hittable.h
#ifndef HITTABLE_H
#define HITTABLE_H
#include"vector.h"
#include"ray.h"
#include"Light.h"
class Hittable;

struct HitRecord {
	const Hittable* hittable;
	vec3 position;
	vec3 normal;
	float p;
	bool frontFace;
	void set_face_normal(const ray& r) {
		frontFace = dot(r.dir, normal)<0;
		normal = frontFace ? normal: -normal;
	}

};
class Hittable {
public:
	virtual bool hit(const ray& r, const float min_p, const float max_p, HitRecord& rec)const = 0;
	virtual vec3 color(const ray& r, const Light& light, HitRecord& rec)const = 0;

};

#endif
