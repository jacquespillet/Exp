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

glm::vec3 random3(glm::vec3 st){
    st = glm::vec3( glm::dot(st,glm::vec3(127.1,311.7, 69.4)),
            glm::dot(st,glm::vec3(269.5,183.3, 103.2)), 
            glm::dot(st,glm::vec3(301.5,241.6, 123.2)));
    return -1.0f + 2.0f*glm::fract(sin(st)*43758.5453123);
}

void interpolant5(float inT, float& t, float& dt) {
    t  = 6 * inT * inT * inT * inT * inT - 15 * inT * inT * inT * inT + 10 * inT * inT * inT;
    dt = 30 * inT * inT * inT * inT - 60  * inT * inT * inT + 30  * inT * inT;
}

struct Noise {
    float value;
    glm::vec4 derivative;
};


Noise PerlinNoise3D(glm::vec3 pos, float _frequency) {
    Noise ret;
    float retVal=0;
    glm::vec4 retDer = glm::vec4(0, 0, 0, 0);

    pos = pos * _frequency;
    glm::vec3 fPart = glm::fract(pos);
    glm::vec3 iPart = glm::floor(pos);

    //Front
    glm::vec3 v0 = random3(iPart +glm::vec3(0, 0, 0));
    glm::vec3 v1 = random3(iPart +glm::vec3(1, 0, 0));
    glm::vec3 v2 = random3(iPart +glm::vec3(0, 1, 0));
    glm::vec3 v3 = random3(iPart +glm::vec3(1, 1, 0));
    
    glm::vec3 v4 = random3(iPart +glm::vec3(0, 0, 1));
    glm::vec3 v5 = random3(iPart +glm::vec3(1, 0, 1));
    glm::vec3 v6 = random3(iPart +glm::vec3(0, 1, 1));
    glm::vec3 v7 = random3(iPart +glm::vec3(1, 1, 1));

    float n0 = glm::dot(v0, fPart - glm::vec3(0, 0, 0));
    float n1 = glm::dot(v1, fPart - glm::vec3(1, 0, 0));
    float n2 = glm::dot(v2, fPart - glm::vec3(0, 1, 0));
    float n3 = glm::dot(v3, fPart - glm::vec3(1, 1, 0));        
    float n4 = glm::dot(v4, fPart - glm::vec3(0, 0, 1));
    float n5 = glm::dot(v5, fPart - glm::vec3(1, 0, 1));
    float n6 = glm::dot(v6, fPart - glm::vec3(0, 1, 1));
    float n7 = glm::dot(v7, fPart - glm::vec3(1, 1, 1));        

    glm::vec3 t = glm::vec3(0,0,0);
    glm::vec3 dt = glm::vec3(1,1,1);
    interpolant5(fPart.x, t.x, dt.x);
    interpolant5(fPart.y, t.y, dt.y);
    interpolant5(fPart.z, t.z, dt.z);

    float a = n0;
    
    float b = n1 - n0;
    float c = n2 - n0;
    float d = n4 - n0;

    float e = n0 - n1 - n2 + n3;
    float f = n0 - n1 - n4 + n5;
    float g = n0 - n2 - n4 + n6;

    float h = -n0 + n1 + n2 - n3 + n4 - n5 - n6 + n7;

    glm::vec3 da = v0;
    
    glm::vec3 db = v1 - v0;
    glm::vec3 dc = v2 - v0;
    glm::vec3 dd = v4 - v0;

    glm::vec3 de = v0 - v1 - v2 + v3;
    glm::vec3 df = v0 - v1 - v4 + v5;
    glm::vec3 dg = v0 - v2 - v4 + v6;

    glm::vec3 dh = -v0 + v1 + v2 - v3 + v4 - v5 - v6 + v7;
    

    retVal = a + b * t.x + c * t.y + d * t.z + 
                e * t.x * t.y + 
                f * t.x * t.z + 
                g * t.y * t.z + 
                h * t.x * t.y * t.z; 
    
    retDer = glm::vec4(da + db * t.x + (dc + de * t.x) * t.y + (dd + df * t.x + (dg + dh * t.x) * t.y) * t.z, 0);
    retDer.x += (b + e * t.y + (f + h * t.y) * t.z) * dt.x;
    retDer.y += (c + e * t.x + (g + h * t.x) * t.z) * dt.y;
    retDer.z += (d + f * t.x + (g + h * t.x) * t.y) * dt.z;        

    ret.value = retVal * 0.5 + 0.5;
    ret.derivative = retDer;
    return ret;
}    

}