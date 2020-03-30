#pragma once

#include "Common/Common.h"
#include "3DEngine/Shader.hpp"

namespace KikooRenderer {
using namespace CoreEngine;
namespace Scene_7_ {
    
Shader GetLightShader() {
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
    
    void main()
    {
        vec3 scaledPos = position + normal * 0.5;
        vec4 finalPosition = modelViewProjectionMatrix * vec4(scaledPos.x, scaledPos.y, scaledPos.z, 1.0f);
        gl_Position = finalPosition;
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    in vec4 fragmentColor; 
    in vec3 fragPos; 

    //output
    layout(location = 0) out vec4 outputColor; 

    void main()
    {
        outputColor=vec4(1,1,1,1);
    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();
    shader.shouldRecompile=false;

    return shader;    
}

}
}