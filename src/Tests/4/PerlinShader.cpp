#include "PerlinShader.hpp"


namespace KikooRenderer {
namespace Scene_4_ {
    
Shader GetPerlinShader() {
    Shader shader;
    shader.vertSrc= R"(
    //attribs
    #version 440
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 uv;
    layout(location = 3) in vec4 color;
    //transforms
    uniform mat4 modelViewProjectionMatrix;
    uniform mat4 modelMatrix;

    out vec2 fragUv;
    out vec3 fragPos;

    void main()
    {
        fragUv = uv;

        // fragPos = (modelMatrix * vec4(position.x, position.y, position.z, 1.0f)).xyz;
        // vec4 finalPosition = modelViewProjectionMatrix * vec4(position.x, position.y, position.z, 1.0f);
        gl_Position = vec4(position.x, position.y, position.z, 1);
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    //output
    layout(location = 0) out vec4 outputColor; 
    
    in vec3 fragPos;
    in vec2 fragUv;

    float random(float st){
        return -1.0 + 2.0*fract(sin(st)*43758.5453123);
    }
    
    float random (vec2 st) {
        return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
    }
    
    float random (vec3 st) {
        return fract(sin(dot(st,
                         vec3(12.9898,78.233, 45.3043)))
                 * 43758.5453123);
    }

    vec2 random2(vec2 st){
        st = vec2( dot(st,vec2(127.1,311.7)),
                dot(st,vec2(269.5,183.3)) );
        return -1.0 + 2.0*fract(sin(st)*43758.5453123);
    }

    vec3 random3(vec3 st){
        st = vec3( dot(st,vec3(127.1,311.7, 69.4)),
                dot(st,vec3(269.5,183.3, 103.2)), 
                dot(st,vec3(301.5,241.6, 123.2)));
        return -1.0 + 2.0*fract(sin(st)*43758.5453123);
    }

    void interpolant3(float inT, out float t, out float dt) {
        t  = 3 * inT * inT - 2 * inT * inT * inT;
        dt = 6 * inT - 6 * inT * inT;
    }

    void interpolant5(float inT, out float t, out float dt) {
        t  = 6 * inT * inT * inT * inT * inT - 15 * inT * inT * inT * inT + 10 * inT * inT * inT;
        dt = 30 * inT * inT * inT * inT - 60  * inT * inT * inT + 30  * inT * inT;
    }


    struct Noise {
        float value;
        vec4 derivative;
    };

    //0 : lerp
    //1 : smoothstep
    //2 : perlin
    uniform vec4 offset;

    uniform int interpMode;
    uniform float frequency;
    uniform int dimension;
    uniform float time;
    uniform int noiseType;

    uniform mat4 camModelMatrix;
    uniform float camFov;
    uniform float camAspectRatio;
    uniform float glossiness;

    const vec3 lightPos = vec3(0, 20, -20);

    Noise ValueNoise1D(float pos, float _frequency, float _interpMode) {
        Noise ret;
        float retVal=0;
        vec4 retDer = vec4(0, 0, 0, 0);

        pos = pos * _frequency;
        float fPart = fract(pos);
        float iPart = floor(pos);

        float v0 = random(iPart);
        float v1 = random(iPart +1);

        float t=0; float dt=0;
        if(_interpMode ==0) {
            t = fPart;
            dt = t;
        } else if(_interpMode == 1) {
            interpolant3(fPart, t, dt);
        } else if(_interpMode == 2) {
            interpolant5(fPart, t, dt);
        }

        float a = v0;
        float b = v1 - v0;

        retVal = v0 +  t * (b);
        retDer.x = dt * b;

        ret.value = retVal;
        ret.derivative = retDer;
        return ret;
    }

    Noise ValueNoise2D(vec2 pos, float _frequency, float _interpMode) {
        Noise ret;
        float retVal=0;
        vec4 retDer = vec4(0, 0, 0, 0);

        pos = pos * _frequency;
        vec2 fPart = fract(pos);
        vec2 iPart = floor(pos);

        float v0 = random(iPart);
        float v1 = random(iPart +vec2(1, 0));
        float v2 = random(iPart +vec2(0, 1));
        float v3 = random(iPart +vec2(1, 1));

        vec2 t = vec2(0,0);
        vec2 dt = vec2(1,1);
        if(_interpMode ==0) {
            t = fPart;
            dt = fPart;
        } else if(_interpMode == 1) {
            interpolant3(fPart.x, t.x, dt.x);
            interpolant3(fPart.y, t.y, dt.y);
        } else if(_interpMode == 2) {
            interpolant5(fPart.x, t.x, dt.x);
            interpolant5(fPart.y, t.y, dt.y);
        }

        float a = v0;
        float b = v1 - v0;
        float c = v2 - v0;
        float d = v0 - v1 - v2 + v3;

        retVal = a + b * t.x + c * t.y + d * t.x * t.y; 
        retDer.x = b * dt.x + d * dt.x * t.y; 
        retDer.y = c * dt.y + d * t.x * dt.y; 


        ret.value = retVal;
        ret.derivative = retDer;
        return ret;
    }

    Noise ValueNoise3D(vec3 pos, float _frequency, float _interpMode) {
        Noise ret;
        float retVal=0;
        vec4 retDer = vec4(0, 0, 0, 0);

        pos = pos * _frequency;
        vec3 fPart = fract(pos);
        vec3 iPart = floor(pos);

        //Front
        float v0 = random(iPart +vec3(0, 0, 0));
        float v1 = random(iPart +vec3(1, 0, 0));
        float v2 = random(iPart +vec3(0, 1, 0));
        float v3 = random(iPart +vec3(1, 1, 0));
        
        float v4 = random(iPart +vec3(0, 0, 1));
        float v5 = random(iPart +vec3(1, 0, 1));
        float v6 = random(iPart +vec3(0, 1, 1));
        float v7 = random(iPart +vec3(1, 1, 1));

        vec3 t = vec3(0,0,0);
        vec3 dt = vec3(1,1,1);
        if(_interpMode ==0) {
            t = fPart;
            dt = fPart;
        } else if(_interpMode == 1) {
            interpolant3(fPart.x, t.x, dt.x);
            interpolant3(fPart.y, t.y, dt.y);
            interpolant3(fPart.z, t.z, dt.z);
        } else if(_interpMode == 2) {
            interpolant5(fPart.x, t.x, dt.x);
            interpolant5(fPart.y, t.y, dt.y);
            interpolant5(fPart.z, t.z, dt.z);
        }

        float a = v0;
        
        float b = v1 - v0;
        float c = v2 - v0;
        float d = v4 - v0;

        float e = v0 - v1 - v2 + v3;
        float f = v0 - v1 - v4 + v5;
        float g = v0 - v2 - v4 + v6;

        float h = -v0 + v1 + v2 - v3 + v4 - v5 - v6 + v7;

        retVal = a + b * t.x + c * t.y + d * t.z + 
                 e * t.x * t.y + 
                 f * t.x * t.z + 
                 g * t.y * t.z + 
                 h * t.x * t.y * t.z; 
        retDer.x = b * dt.x +
                 e * dt.x * t.y + 
                 f * dt.x * t.z +
                 h * dt.x * t.y * t.z; 
        retDer.y = c * dt.y+
                 e * t.x * dt.y + 
                 g * dt.y * t.z + 
                 h * t.x * dt.y * t.z; 

        ret.value = retVal;
        ret.derivative = retDer;
        return ret;
    }

    Noise PerlinNoise2D(vec2 pos, float _frequency, float _interpMode) {
        Noise ret;
        float retVal=0;
        vec4 retDer = vec4(0, 0, 0, 0);

        pos = pos * _frequency;
        vec2 fPart = fract(pos);
        vec2 iPart = floor(pos);

        vec2 v0 = random2(iPart);
        vec2 v1 = random2(iPart +vec2(1, 0));
        vec2 v2 = random2(iPart +vec2(0, 1));
        vec2 v3 = random2(iPart +vec2(1, 1));



        vec2 t = vec2(0,0);
        vec2 dt = vec2(1,1);
        if(_interpMode ==0) {
            t = fPart;
            dt = fPart;
        } else if(_interpMode == 1) {
            interpolant3(fPart.x, t.x, dt.x);
            interpolant3(fPart.y, t.y, dt.y);
        } else if(_interpMode == 2) {
            interpolant5(fPart.x, t.x, dt.x);
            interpolant5(fPart.y, t.y, dt.y);
        }

        float n0 = dot(v0, fPart - vec2(0, 0));
        float n1 = dot(v1, fPart - vec2(1, 0));
        float n2 = dot(v2, fPart - vec2(0, 1));
        float n3 = dot(v3, fPart - vec2(1, 1));

        float a = n0;
        float b = n1 - n0;
        float c = n2 - n0;
        float d = n0 - n1 - n2 + n3;

        vec2 da = v0;
        vec2 db = v1 - v0;
        vec2 dc = v2 - v0;
        vec2 dd = v0 - v1 - v2 + v3;

        retVal = a + b * t.x + c * t.y + d * t.x * t.y;

        retDer.xy = da + db * t.x + dc * t.y + dd * t.x * t.y;
        retDer.x += b * dt.x + d * dt.x * t.y;
        retDer.y += c * dt.y + d * t.x * dt.y;

        ret.value = retVal * 0.5 + 0.5;
        ret.derivative = retDer;
        return ret;
    }

    Noise PerlinNoise3D(vec3 pos, float _frequency, float _interpMode) {
        Noise ret;
        float retVal=0;
        vec4 retDer = vec4(0, 0, 0, 0);

        pos = pos * _frequency;
        vec3 fPart = fract(pos);
        vec3 iPart = floor(pos);

        //Front
        vec3 v0 = random3(iPart +vec3(0, 0, 0));
        vec3 v1 = random3(iPart +vec3(1, 0, 0));
        vec3 v2 = random3(iPart +vec3(0, 1, 0));
        vec3 v3 = random3(iPart +vec3(1, 1, 0));
        
        vec3 v4 = random3(iPart +vec3(0, 0, 1));
        vec3 v5 = random3(iPart +vec3(1, 0, 1));
        vec3 v6 = random3(iPart +vec3(0, 1, 1));
        vec3 v7 = random3(iPart +vec3(1, 1, 1));

        float n0 = dot(v0, fPart - vec3(0, 0, 0));
        float n1 = dot(v1, fPart - vec3(1, 0, 0));
        float n2 = dot(v2, fPart - vec3(0, 1, 0));
        float n3 = dot(v3, fPart - vec3(1, 1, 0));        
        float n4 = dot(v4, fPart - vec3(0, 0, 1));
        float n5 = dot(v5, fPart - vec3(1, 0, 1));
        float n6 = dot(v6, fPart - vec3(0, 1, 1));
        float n7 = dot(v7, fPart - vec3(1, 1, 1));        

        vec3 t = vec3(0,0,0);
        vec3 dt = vec3(1,1,1);
        if(_interpMode ==0) {
            t = fPart;
        } else if(_interpMode == 1) {
            interpolant3(fPart.x, t.x, dt.x);
            interpolant3(fPart.y, t.y, dt.y);
            interpolant3(fPart.z, t.z, dt.z);
        } else if(_interpMode == 2) {
            interpolant5(fPart.x, t.x, dt.x);
            interpolant5(fPart.y, t.y, dt.y);
            interpolant5(fPart.z, t.z, dt.z);
        }

        float a = n0;
        
        float b = n1 - n0;
        float c = n2 - n0;
        float d = n4 - n0;

        float e = n0 - n1 - n2 + n3;
        float f = n0 - n1 - n4 + n5;
        float g = n0 - n2 - n4 + n6;

        float h = -n0 + n1 + n2 - n3 + n4 - n5 - n6 + n7;

        vec3 da = v0;
        
        vec3 db = v1 - v0;
        vec3 dc = v2 - v0;
        vec3 dd = v4 - v0;

        vec3 de = v0 - v1 - v2 + v3;
        vec3 df = v0 - v1 - v4 + v5;
        vec3 dg = v0 - v2 - v4 + v6;

        vec3 dh = -v0 + v1 + v2 - v3 + v4 - v5 - v6 + v7;
        

        retVal = a + b * t.x + c * t.y + d * t.z + 
                 e * t.x * t.y + 
                 f * t.x * t.z + 
                 g * t.y * t.z + 
                 h * t.x * t.y * t.z; 
        
		retDer.xyz = da + db * t.x + (dc + de * t.x) * t.y + (dd + df * t.x + (dg + dh * t.x) * t.y) * t.z;
		retDer.x += (b + e * t.y + (f + h * t.y) * t.z) * dt.x;
		retDer.y += (c + e * t.x + (g + h * t.x) * t.z) * dt.y;
		retDer.z += (d + f * t.x + (g + h * t.x) * t.y) * dt.z;        

        ret.value = retVal * 0.5 + 0.5;
        ret.derivative = retDer;
        return ret;
    }    

    float RaySphereTest(vec3 rayOrig, vec3 rayDir, vec3 spherePos, float radius, out vec3 pos, out vec3 normal, out vec2 uv) {
        vec3 oc = rayOrig - spherePos;
        float a = dot(rayDir, rayDir);
        float b = 2 * dot(oc, rayDir);
        float c = dot(oc, oc) - radius * radius;
        float delta = b*b - 4 * a * c;
        if(delta < 0) {
            return -1;
        } else {
            float t = (- b - sqrt(delta)) / (2 * a);
            pos = rayOrig + rayDir * t;
            normal = normalize(pos - spherePos);
            
            float phi = atan(normal.z, normal.x);
            float theta = asin(normal.y);

            float u = (phi + 3.14) / (2.0f * 3.14);
            float v = (theta + 3.14/2.0f) / 3.14;

            uv = vec2(u, v);

            return t;
        }        
        return -1;
    }

    void main()
    {
        vec2 clipSpaceCoords = fragUv * 2 - 1;

        vec4 rayOrig = camModelMatrix * vec4(0, 0, 0, 1);
        vec4 rayDir = vec4(0, 0, 1, 0);
        rayDir.x = abs(tan(camFov * 0.5)) * clipSpaceCoords.x * camAspectRatio;
        rayDir.y = abs(tan(camFov * 0.5)) * clipSpaceCoords.y;
        rayDir = camModelMatrix * rayDir;
        rayDir = normalize(rayDir);

        float distance=0;
        vec3 spherePos = vec3(0, 0, 0);
        float sphereRadius = 10;
        vec3 sPos;
        vec3 sNorm;
        vec2 sUv;
        float intersects = RaySphereTest(rayOrig.xyz, rayDir.xyz, spherePos, sphereRadius, sPos, sNorm, sUv);

        vec4 finalColor = vec4(0, 0, 0, 1);
        if(intersects > 0) {
            Noise n;
            if(noiseType == 0) {
                if(dimension==1) {
                    n = ValueNoise1D(sUv.x, frequency, interpMode);
                    sNorm.x -= n.derivative.x;
                    sNorm = normalize(sNorm);
                } else if(dimension==2) {
                    n = ValueNoise2D(sUv, frequency, interpMode);
                    sNorm.x -= n.derivative.x;
                    sNorm.y -= n.derivative.y;
                    sNorm = normalize(sNorm);
                } else if(dimension==3) {
                    n = ValueNoise3D(vec3(sUv, time), frequency, interpMode);
                    sNorm.x -= n.derivative.x;
                    sNorm.y -= n.derivative.y;
                    sNorm = normalize(sNorm);
                }
            } else if(noiseType == 1) {
                if(dimension==1) {
                    n = ValueNoise1D(sUv.x, frequency, interpMode);
                    sNorm.x -= n.derivative.x;
                    sNorm = normalize(sNorm);
                }  
                else if(dimension==2) {
                    n = PerlinNoise2D(sUv, frequency, interpMode);
                    sNorm.x -= n.derivative.x;
                    sNorm.y -= n.derivative.y;
                    sNorm = normalize(sNorm);
                }  else if(dimension==3) {
                    n = PerlinNoise3D(vec3(sUv, time), frequency, interpMode);
                    sNorm.x -= n.derivative.x;
                    sNorm.y -= n.derivative.y;
                    sNorm = normalize(sNorm);
                }                
            }

            vec3 localNormal = sNorm;
            vec3 fragPos = rayOrig.xyz + rayDir.xyz * intersects;

            vec3 fragToLight = normalize(lightPos - fragPos);
            vec3 fragToEye   = normalize(rayOrig.xyz   - fragPos);

            float NDotL = dot(localNormal, fragToLight);
            float diffuseIntensity = clamp(NDotL, 0, 1);

            vec3 halfVec = normalize(fragToLight + fragToEye);
            float NDotH = dot(localNormal, halfVec);
            float specularIntensity = pow(clamp(NDotH, 0, 1), glossiness);
            
            vec4 fragColor = 0.5 * vec4(n.value,n.value,n.value, 1);
            finalColor = fragColor + diffuseIntensity *  fragColor + specularIntensity *  fragColor;
        }

        outputColor = finalColor;
    } 
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}