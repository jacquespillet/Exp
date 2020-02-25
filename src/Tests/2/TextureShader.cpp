#include "PlaneShader.hpp"


namespace KikooRenderer {
namespace Scene_2_ {
    
Shader GetTextureShader() {
    Shader shader;
    shader.vertSrc= R"(
    //attribs
    #version 440
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 uv;
    layout(location = 3) in vec4 color;

    //outputs
    out vec2 fragUv;
    //main


    void main()
    {
        fragUv = uv;
        gl_Position = vec4(position, 1);
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    in vec2 fragUv;

    //uniforms
    uniform float time;
    //output
    layout(location = 0) out vec4 outputColor; 
    //main
    
    //Common params
    // const float speed = 3;
    
    //Gertsner params
    // const float q=0.8;

    uniform int numWaves;
    uniform vec2 directions[40];
    uniform float waveLengths[40];
    uniform float amplitudes[40];    
    uniform float speeds[40];    
    uniform float qs[40];    

    vec3 GetGertsnerWave(vec3 pos, float _waveLength, float _amplitude, float _speed, vec2 _direction, float _k, float _q,  out vec3 normal) {
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


    void main()
    {  
        vec3 normal = vec3(0, 0, 0);
        vec4 newPos=vec4(fragUv.x * 10, 0, fragUv.y * 10, 1);

        for(int i=0; i<numWaves; i++) {
            vec3 waveNormal;
            vec3 wavePos = GetGertsnerWave(newPos.xyz, waveLengths[i], amplitudes[i], speeds[i], directions[i], 0, qs[i], waveNormal); 
            newPos += vec4(wavePos, 0);
            normal += waveNormal;
        }
        
        normal = normal;

        outputColor = vec4(normal, 1);
    }
    )";

    std::cout << "Texture: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}