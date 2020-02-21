#pragma once
#include "Common/Common.h"
namespace KikooRenderer
{
	
	
namespace CoreEngine
{
	

class Shader
{		
	private:
		bool compiled; 
		int identifier = 0;
		
	public:
		std::string name; 
		
		//shader source	
		std::string vertSrc;
		std::string fragSrc;
		std::string geometrySrc;
	
		//shader programs
		int programShaderObject;
		int vertexShaderObject;
		int geometryShaderObject;
		int fragmentShaderObject;
		

		Shader();
		
		void SetId(int id);
		int GetId();

		void Compile();

		Shader& operator=(const Shader& other);

		// QLayout* GetParamsLayout();
		// void SetParams(ShaderParams* params);
		// void SetParamsUniforms();
};
	
	
}


}