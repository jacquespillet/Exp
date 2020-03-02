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
    uniform mat4 modelMatrix;

    out vec2 fragUv;
    out vec3 fragPos;

    void main()
    {
        fragUv = uv;

        fragPos = (modelMatrix * vec4(position.x, position.y, position.z, 1.0f)).xyz;
        vec4 finalPosition = modelViewProjectionMatrix * vec4(position.x, position.y, position.z, 1.0f);
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

    uniform sampler2D normalMap;
    uniform sampler2D groundAlbedo;
    uniform sampler2D groundNormal;
    uniform vec3 eyePos;
    
    const vec3 lightPos = vec3(0, 10, 10);

    void main()
    {
        vec3 pNormal = normalize(texture(normalMap, fragUv).xyz); 
        float caustic = dot(pNormal, vec3(0, 1, 0)) * 0.85;
        
        vec4 albedo = texture(groundAlbedo, fragUv);
        vec3 normal = texture(groundNormal, fragUv).xzy * 2.0 - 1.0;
        normal = normalize(normal * 2);

        vec3 fragToLight = normalize(lightPos - fragPos);
        vec3 fragToEye   = normalize(eyePos   - fragPos);

        float NDotL = dot(normal, fragToLight);
        float diffuseIntensity = clamp(NDotL, 0, 1);

        
        outputColor = diffuseIntensity * albedo * 0.6 + vec4(caustic,caustic,caustic, 0);
    } 
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}