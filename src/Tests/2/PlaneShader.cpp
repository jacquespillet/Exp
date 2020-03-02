#include "PlaneShader.hpp"


namespace KikooRenderer {
namespace Scene_2_ {
    
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

    uniform sampler2D posMap;
    uniform sampler2D normalMap;

    void main()
    {
        vec3 normal = vec3(0, 1, 0);
        vec4 newPos=vec4(position, 1);

        fragPos = (modelMatrix * newPos).xyz;
        fragColor = vec4(0.2, 0.2, 0.7, 1);
        // fragColor = texture(posMap, uv); 
        fragNormal = texture(normalMap, uv).xyz;
        fragUv = uv;

        // newPos.xyz = texture(posMap, uv).xyz;
        newPos.y = texture(posMap, uv).y;

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
    uniform sampler2D normalMap;

    //output
    layout(location = 0) out vec4 outputColor; 
    //main
    const vec3 lightPos = vec3(0, 10, 10);
    
    void main()
    {
        vec3 localNormal = texture(normalMap, fragUv).xyz;
        localNormal = normalize(localNormal);

        vec3 fragToLight = normalize(lightPos - fragPos);
        vec3 fragToEye   = normalize(eyePos   - fragPos);

        float NDotL = dot(localNormal, fragToLight);
        float diffuseIntensity = clamp(NDotL, 0, 1);

        vec3 halfVec = normalize(fragToLight + fragToEye);
        float NDotH = dot(localNormal, halfVec);
        float specularIntensity = pow(clamp(NDotH, 0, 1), 8);
        
        outputColor = vec4(0.2, 0.2, 0.2, 1) + diffuseIntensity * fragColor + specularIntensity * fragColor;
        // outputColor = fragColor;
    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}