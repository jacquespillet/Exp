#include "TransformComponent.hpp"

namespace KikooRenderer {
namespace CoreEngine {

TransformComponent::TransformComponent() : Component("Transform") {
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);   
}
void TransformComponent::OnStart(){}
void TransformComponent::OnEnable(){}
void TransformComponent::OnUpdate(){}
void TransformComponent::OnRender(){} 

glm::mat4 TransformComponent::GetModelMatrix() {
    const float DEGTORAD = 0.01745329251f; 
	
	glm::mat4 translateM = glm::translate(glm::mat4(1.0f), this->position);
	
	glm::mat4 scaleM = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 rotxPM = glm::rotate(glm::mat4(1.0f), rotation.x * DEGTORAD, glm::vec3(1.0f, 0.0f, 0.0f));//rot x axis
	glm::mat4 rotyPM = glm::rotate(glm::mat4(1.0f), rotation.y * DEGTORAD, glm::vec3(0.0f, 1.0f, 0.0f));//rot y axis
	glm::mat4 rotzPM = glm::rotate(glm::mat4(1.0f), rotation.z * DEGTORAD, glm::vec3(0.0f, 0.0f, 1.0f));//rot z axis

	glm::mat4 rotM = rotyPM * rotxPM * rotzPM; 	
		
	return translateM * rotM * scaleM;
}

}
}