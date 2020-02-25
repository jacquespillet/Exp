#include "PlaneShader.hpp"


namespace KikooRenderer {
namespace Scene_2_ {
    
Shader GetGroundShader() {
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

    out vec2 fragUv;

    void main()
    {
        fragUv = uv;

        vec4 finalPosition = modelViewProjectionMatrix * vec4(position.x, position.y, position.z, 1.0f);
        gl_Position = vec4(finalPosition.x, finalPosition.y, finalPosition.z, finalPosition.w);
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    //output
    layout(location = 0) out vec4 outputColor; 
    
    in vec2 fragUv;
    uniform sampler2D normalMap;

    void main()
    {
        vec3 normal = normalize(texture(normalMap, fragUv).xyz); 
        vec3 refracted = refract(vec3(0, 1, 0), -normal, 1.30);
        float caustic = dot(refracted, vec3(0, 1, 0));
        
        // outputColor = vec4(normal, 1);
        outputColor = texture(normalMap, fragUv); 
        // outputColor = vec4(caustic,caustic,caustic, 1);
    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}