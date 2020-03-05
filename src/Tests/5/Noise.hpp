#pragma once 
#include "Common/Common.h"

namespace KikooRenderer {

float hash(float p) { p = glm::fract(p * 0.011); p *= p + 7.5; p *= p + p; return glm::fract(p); }

float hash(glm::vec2 p) {
    glm::vec3 p3 = glm::fract(glm::vec3(p.x, p.y, p.x) * 0.13); 
    p3 += glm::dot(p3, glm::vec3(p3.y, p3.z, p3.x) + glm::vec3(3.333)); 
    return glm::fract((p3.x + p3.y) * p3.z); 
}

float noise(float x) {
    float i = glm::floor(x);
    float f = glm::fract(x);
    float u = f * f * (3.0 - 2.0 * f);
    return glm::mix(hash(i), hash(i + 1.0), u);
}


float noise(glm::vec2 x) {
    glm::vec2 i = glm::floor(x);
    glm::vec2 f = glm::fract(x);

	// Four corners in 2D of a tile
	float a = hash(i);
    float b = hash(i + glm::vec2(1.0, 0.0));
    float c = hash(i + glm::vec2(0.0, 1.0));
    float d = hash(i + glm::vec2(1.0, 1.0));

    // Simple 2D lerp using smoothstep envelope between the values.
	// return vec3(mix(mix(a, b, smoothstep(0.0, 1.0, f.x)),
	//			mix(c, d, smoothstep(0.0, 1.0, f.x)),
	//			smoothstep(0.0, 1.0, f.y)));

	// Same code, with the clamps in smoothstep and common subexpressions
	// optimized away.
    glm::vec2 u = f * f * (glm::vec2(3.0) - 2.0 * f);
	return glm::mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}


}