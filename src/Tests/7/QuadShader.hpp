#pragma once

#include "Common/Common.h"
#include "3DEngine/Shader.hpp"

namespace KikooRenderer {
using namespace CoreEngine;
namespace Scene_7_ {
    
Shader GetQuadShader() {
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
    //outputs
    out vec4 fragmentColor;  
    out vec3 fragPos;
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
    in vec4 fragmentColor; 
    in vec3 fragPos; 
    in vec2 fragUv; 

    //output
    layout(location = 0) out vec4 outputColor; 

    //main
    uniform sampler2D depthMap;

    void main()
    {
        outputColor = texture(depthMap, fragUv);
        // float depth  = texture(depthMap, fragUv).x;
        // if(depth < 0.5) {
        //     outputColor = vec4(fragUv, 0, 1);
        // }else outputColor = vec4(fragUv * 0.9,0, 1);
        // outputColor = vec4(fragUv,0, 1);
    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;    
}

}
}