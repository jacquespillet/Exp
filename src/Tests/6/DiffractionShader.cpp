#include "DiffractionShader.hpp"


namespace KikooRenderer {
namespace Scene_6_ {
    
Shader GetDiffractionShader() {
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

    uniform vec3 eyePos;    
    const vec3 lightPos = vec3(3, 3, 3);

    uniform float d = 1;
    uniform float r = 0.5;
    uniform samplerCube skybox;

    vec3 blend3 (vec3 x)  {    
        vec3 y = 1 - x * x;
        y = max(y, vec3 (0, 0, 0));
        return y;
    } 

    void main()
    {          
        float dist =length(fragPos);
        if(length(fragPos) >= 0.5) discard;

        vec3 fragToLight = normalize(lightPos - fragPos); // fragtolight
        vec3 fragToEye = normalize(eyePos - fragPos); // fragtoeye

        vec3 H = fragToLight + fragToEye; //halfway vector
        
        vec3 N = vec3(0, 1, 0);
        vec3 T = normalize(vec3(-fragPos.z, 0, fragPos.x));
        
        vec3 reflected = reflect(-fragToEye, N);
    	
        vec4 hiliteColor = vec4(texture(skybox, normalize(reflected)).xyz, 1);

        float u = dot(T, H) * d; //project the H vector onto the tangent plane
        
        float w = dot(N, H); //Project H onto N

        float e = r * u / w;
        float c = exp(-e * e);
        vec4 anis = hiliteColor * vec4(c, c, c, 1);

        if (u < 0) u = -u;

        vec4 cdiff = vec4(0, 0, 0, 1);
        for (int n = 1; n < 8; n++)    {
            float y = 2 * u / n - 1;
            cdiff.xyz += blend3(vec3(4 * (y - 0.75), 4 * (y - 0.5),4 * (y - 0.25)));
        }
        
    
        outputColor = cdiff + anis;
    } 
    )";

    std::cout << "Plane: Compiling shader" << std::endl; 
    shader.Compile();

    return shader;
}

}
}