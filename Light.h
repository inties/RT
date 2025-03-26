#pragma once
#include"vector.h"
#include"somemath.h"
struct Light {
	vec3 pos;
	vec3 dir;
	vec3 color;
	Light(vec3 pos, vec3 dir, vec3 color): pos(pos),dir(normalize(dir)), color(color) {
		
		
	};
	
	
};