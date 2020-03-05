#include "GrassShader.hpp"


namespace KikooRenderer {
namespace Scene_5_ {
    
Shader GetGrassShader() {
    Shader shader;
    shader.vertSrc= R"(
    //attribs
    #version 440
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 uv;
    layout(location = 3) in vec4 color;
    layout(location = 5) in mat4 modelMatrix;
    layout(location = 9) in vec4 additionalData1;
    layout(location = 10) in vec4 additionalData2;
    //transforms
    // uniform mat4 modelViewProjectionMatrix;
    // uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;

    out vec2 fragUv;
    out vec3 fragPos;

    void main()
    {
        fragUv = uv;
        mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

        fragPos = (modelMatrix * vec4(position.x, position.y, position.z, 1.0f)).xyz;
        vec4 finalPosition = mvp * vec4(position.x, position.y, position.z, 1.0f);
        gl_Position = vec4(finalPosition.x, finalPosition.y, finalPosition.z, finalPosition.w);
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    //output
    layout(location = 0) out vec4 outputColor; 
    
    in vec3 fragPos;
    in vec2 fragUv;

    uniform sampler2D grassTex;


    void main()
    {
        outputColor = texture(grassTex, fragUv);
    } 
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}