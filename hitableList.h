#pragma once
#include"hitable.h"
#include<memory>
#include<vector>
using std::shared_ptr;
using std::vector;
class hitableList {
public:
	vector<shared_ptr<Hittable>>objects;
public:
	hitableList(const shared_ptr<Hittable>&p) {
		add(p);
	}
	hitableList() {

	}
	void add(const shared_ptr<Hittable>& p) {
		objects.push_back(p);
	}
	void clear() {
		objects.clear();
	}
	bool hit(const ray& r,float p_min,float p_max, HitRecord& rec)const;
};
bool hitableList::hit(const ray& r, float p_min, float p_max, HitRecord& rec)const {
	float p_current=p_max;
	HitRecord rec_temp;
	bool hit=false;
	for (auto object : objects) {
		if (object->hit(r, p_min, p_current, rec_temp)) {
			hit = true;
			p_current = rec_temp.p;
			rec = rec_temp;
		}
	}
	return hit;


}