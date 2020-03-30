#include "ObjectShader.hpp"


namespace KikooRenderer {
namespace Scene_7_ {
    
Shader GetObjectShader() {
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
    out vec3 fragNormal;
    //main
    void main()
    {
        //compute outputs
        fragmentColor = color;
        fragNormal = normal;
        fragPos = position;
        vec4 finalPosition = modelViewProjectionMatrix * vec4(position.x, position.y, position.z, 1.0f);
        gl_Position = finalPosition;
    }
    )";

    shader.fragSrc = R"(
    //inputs
    #version 440
    in vec4 fragmentColor; 
    in vec3 fragPos; 
    in vec3 fragNormal;

    //output
    layout(location = 0) out vec4 outputColor; 

    uniform vec3 lightPos;

    //main
    uniform sampler2D depthMap;
    uniform mat4 lightMvp;
    uniform vec3 eyePos;

    // const float sigma = 1;
    uniform float sigma;
    uniform float lightInt;
    void main()
    {
        // outputColor = vec4(1,1,1,1);
        // vec3 fragToLight = normalize(lightPos - fragPos);

        //use the mvp of the light to project the point onto light space
        vec4 fragPosLightSpace = lightMvp * vec4(fragPos, 1);
        vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
        float currentDepth = projCoords.z;
        projCoords = projCoords * 0.5 + 0.5;
        
        //Check the distance at this pixel
        float closestFromLight = texture(depthMap, projCoords.xy).r;
  
        // //World space distance
        float sssFactor = min(abs(closestFromLight - currentDepth), 1.5);
        sssFactor = 1 - exp(sssFactor * sigma) * lightInt; 
        outputColor = vec4(sssFactor,sssFactor,sssFactor,1);


        // outputColor = vec4(1, 1, 1, 1) - vec4(travelledDistance, travelledDistance, travelledDistance, 0) * 1.5;
        
        // if(closestFromLight < currentDepth) outputColor = vec4(0,0,0, 1);
        // else  outputColor = vec4(1,1,1,1);

        // float sssFactor = travelledDistance;

        // outputColor = vec4(travelledDistance,travelledDistance,travelledDistance, 1);


        // vec3 localNormal = normalize(fragNormal);
        // vec3 fragToEye   = normalize(eyePos   - fragPos);

        // float NDotL = dot(localNormal, fragToLight);
        // float diffuseIntensity = clamp(NDotL, 0, 1);

        // vec3 halfVec = normalize(fragToLight + fragToEye);
        // float NDotH = dot(localNormal, halfVec);
        // float specularIntensity = pow(clamp(NDotH, 0, 1), 64);
        
        // outputColor = vec4(0.2, 0.2, 0.2, 1) + diffuseIntensity * vec4(0.5, 0.2, 0.2, 0) + specularIntensity * vec4(0.5, 0.2, 0.2, 0);
        
        // outputColor = exp(-si * sigma_t) * lightColor;

        // outputColor *= exp(sssFactor * sigma);

    }
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}