#include "PlaneShader.hpp"


namespace KikooRenderer {
namespace Scene_1_ {
    
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
    uniform mat4 modelMatrix;
    uniform vec4 materialColor; 
    uniform float time;
    //outputs
    out vec4 fragColor;  
    out vec3 fragNormal;
    out vec3 fragPos;
    out vec2 fragUv;
    //main

    //Common params
    // const float waveLength = 2;
    // const float amplitude = 2;
    // const float speed = 2;
    // const vec2 direction = vec2(1, 0);
    // const float k = 1.5;
    
    //Gertsner params
    // const float q=1;

    uniform int numWaves;
    uniform vec2 directions[40];
    uniform float waveLengths[40];
    uniform float amplitudes[40];
    uniform float speeds[40];
    uniform float qs[40];


    vec3 GetGertsnerWave(vec3 pos, float _waveLength, float _amplitude, float _speed, vec2 _direction, float _q,  out vec3 normal) {
        float Qi = _q / (_waveLength * _amplitude * numWaves);

        vec3 ret = pos;

        float dotTerm = dot(_direction, pos.xz);
        ret.y = _amplitude * sin(_waveLength * dotTerm + time * _speed);

        ret.x = (Qi * _amplitude * _direction.x * cos(_waveLength * dotTerm + time*_speed));
        ret.z = (Qi * _amplitude * _direction.y * cos(_waveLength * dotTerm + time*_speed));

        float wa = _waveLength * _amplitude;
        float S = sin(_waveLength * dotTerm + time*_speed);
        float C = cos(_waveLength * dotTerm + time*_speed);

        normal = vec3(0, 0, 0);
        normal.x = _direction.x * wa * C;
        normal.z = _direction.y * wa * C;
        normal.y =  (Qi * wa * S);
        // normal = normal;

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
        vec3 normal = vec3(0, 1, 0);
        vec4 newPos=vec4(position, 1);

        for(int i=0; i<numWaves; i++) {
            vec3 waveNormal;
            vec3 wavePos = GetGertsnerWave(newPos.xyz, waveLengths[i], amplitudes[i], speeds[i], directions[i], qs[i], waveNormal); 
            newPos += vec4(wavePos, 0);

            normal -= waveNormal;
        }

        fragPos = (modelMatrix * newPos).xyz;
        fragColor = vec4(0.2, 0.2, 0.7, 1);
        // fragNormal = normalize(normal);
        fragNormal = normal;
        fragUv = uv;

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
    in vec2 fragUv;

    //uniforms
    uniform vec3 eyePos;
    uniform sampler2D albedoTexture;

    //output
    layout(location = 0) out vec4 outputColor; 
    //main
    const vec3 lightPos = vec3(0, 10, 0);
    
    void main()
    {
        vec3 localNormal = fragNormal - texture(albedoTexture, fragUv).xyz;
        localNormal = normalize(localNormal);
        // vec3 localNormal = normalize(fragNormal);

        vec3 fragToLight = normalize(lightPos - fragPos);
        vec3 fragToEye   = normalize(eyePos   - fragPos);

        float NDotL = dot(localNormal, fragToLight);
        float diffuseIntensity = clamp(NDotL, 0, 1);

        vec3 halfVec = normalize(fragToLight + fragToEye);
        float NDotH = dot(localNormal, halfVec);
        float specularIntensity = pow(clamp(NDotH, 0, 1), 64);
        
        outputColor = vec4(0.2, 0.2, 0.2, 1) + diffuseIntensity * fragColor + specularIntensity * fragColor;
        // outputColor = vec4(0.2, 0.2, 0.2, 1) + diffuseIntensity * fragColor;
        // outputColor = texture(albedoTexture, fragUv); 
        // outputColor = vec4(fragUv, 0, 1);
    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}