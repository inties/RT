#pragma once
class Hittable;
class material;
struct HitRecord {
	const Hittable* hittable;
	shared_ptr<material>mat_ptr;
	vec3 position;
	vec3 normal;
	float p;
	bool frontFace;
	void set_face_normal(const ray& r) {
		frontFace = dot(r.dir, normal) < 0;
		normal = frontFace ? normal : -normal;
	}

};