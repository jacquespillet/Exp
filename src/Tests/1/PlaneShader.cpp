#include "PlaneShader.hpp"


namespace KikooRenderer {
namespace CoreEngine {
    
Shader GetShader() {
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
    uniform mat4 mMatrix;
    uniform vec4 materialColor; 
    uniform float time;
    //outputs
    out vec4 fragColor;  
    out vec3 fragNormal;
    out vec3 fragPos;
    //main

    //Common params
    const float waveLength = 2;
    const float amplitude = 2;
    const float speed = 1;
    const vec2 direction = vec2(1, 0);
    const float k = 1.5;
    
    //Gertsner params
    const float q=0.5;
    const int numWaves = 1;

    vec3 GetGertsnerWave(vec3 pos, float _waveLength, float _amplitude, float _speed, vec2 _direction, float _k, float _q,  out vec3 normal) {
        float Qi = q / (_waveLength * _amplitude * numWaves);

        vec3 ret = pos;

        float dotTerm = dot(direction, pos.xz);
        ret.y = _amplitude * sin(_waveLength * dotTerm + time * _speed);

        ret.x = pos.x + (Qi * _amplitude * _direction.x * cos(_waveLength * dotTerm + time*_speed));
        ret.z = pos.z + (Qi * _amplitude * _direction.y * cos(_waveLength * dotTerm + time*_speed));

        float wa = _waveLength * _amplitude;
        float S = sin(_waveLength * dotTerm + time*_speed);
        float C = sin(_waveLength * dotTerm + time*_speed);


        normal = vec3(0, 0, 0);
        normal.x = -_direction.x * wa * C;
        normal.z = -_direction.y * wa * C;
        normal.y = 1 - (Qi * wa * S);

        return ret;
    }

    float GetSineWave(vec2 xzPos, float _waveLength, float _amplitude, float _speed, vec2 _direction, float _k, out vec3 normal) {
        float dotTerm = dot(_direction, xzPos);

        float ret = 2 * _amplitude * pow( (sin( dotTerm * _waveLength + time * _speed) + 1) / 2, _k);

        float xDerivative = _k * _direction.x * _waveLength * _amplitude * (2 * _amplitude * pow( (sin( dotTerm * _waveLength + time * _speed) + 1) / 2, _k-1)) * cos(dotTerm * _waveLength+ time * _speed);
        float zDerivative = _k * _direction.y * _waveLength * _amplitude * (2 * _amplitude * pow( (sin( dotTerm * _waveLength + time * _speed) + 1) / 2, _k-1)) * cos(dotTerm * _waveLength+ time * _speed);
        normal = normalize(vec3(-xDerivative, 1, -zDerivative));

        return ret;
    }

    void main()
    {
        vec3 normal;
        vec4 newPos=vec4(position, 1);
        // newPos.y = GetSineWave(newPos.xz, waveLength, amplitude, speed, direction, k ,normal);
        newPos = vec4(GetGertsnerWave(newPos.xyz, waveLength, amplitude, speed, direction, k, q, normal), 1);
        
        fragPos = (mMatrix * newPos).xyz;
        fragColor = vec4(0.2, 0.2, 0.7, 1);
        fragNormal = normal;
        

        vec4 finalPosition = modelViewProjectionMatrix * vec4(newPos.x, newPos.y, newPos.z, 1.0f);
        gl_Position = vec4(finalPosition.x, finalPosition.y, finalPosition.z, finalPosition.w);
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    in vec4 fragColor; 
    in vec3 fragNormal;
    in vec3 fragPos;

    //uniforms
    uniform vec3 eyePos;
    //output
    layout(location = 0) out vec4 outputColor; 
    //main
    const vec3 lightPos = vec3(10, 10, 10);
    
    void main()
    {
        vec3 fragToLight = normalize(lightPos - fragPos);
        vec3 fragToEye   = normalize(eyePos   - fragPos);

        float NDotL = dot(fragNormal, fragToLight);
        float diffuseIntensity = clamp(NDotL, 0, 1);

        vec3 halfVec = normalize(fragToLight + fragToEye);
        float NDotH = dot(fragNormal, halfVec);
        float specularIntensity = pow(clamp(NDotH, 0, 1), 8);
        
        // outputColor = diffuseIntensity * fragColor + specularIntensity * fragColor;
        outputColor = diffuseIntensity * fragColor;
    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}