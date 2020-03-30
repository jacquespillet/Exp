#include "StandardShaders.hpp"


namespace KikooRenderer
{
namespace CoreEngine
{

void StandardShaders::Compile()
{	
unlitMeshShader.vertSrc= R"(
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
//main
void main()
{
	//compute outputs
	fragmentColor = color;
	fragPos = (modelMatrix * vec4(position.x, position.y, position.z, 1.0f)).xyz;
	vec4 finalPosition = modelViewProjectionMatrix * vec4(position.x, position.y, position.z, 1.0f);
	gl_Position = finalPosition;
}
)";

unlitMeshShader.fragSrc = R"(
//inputs
#version 440
in vec4 fragmentColor; 
in vec3 fragPos; 

//output
layout(location = 0) out vec4 outputColor; 

//main
uniform samplerCube skybox;
uniform int hasSkybox;
void main()
{
	if(hasSkybox>0) {
		outputColor = vec4(texture(skybox, normalize(fragPos)).xyz, 1);
	} else {
		outputColor = vec4(0.8, 0.8, 0.8, 1);
	}
}
)";

std::cout << "StandardShaders: Compiling unlitMeshShader" << std::endl; 
unlitMeshShader.Compile();

}	
}
}