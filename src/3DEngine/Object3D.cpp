#include "Object3D.hpp"

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLFunctions_3_2_Core>
#define GLV QOpenGLFunctions_3_2_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}


namespace KikooRenderer {

namespace CoreEngine {

Object3D::Object3D(std::string _name, Scene* _scene, Shader _shader) {
    this->name = _name;
    this->scene = _scene;

	std::cout << "RESETING0" << std::endl;
    this->shader = _shader;
	std::cout << "RESETING1" << std::endl;
}

void Object3D::AddComponent(Component* component) {
    this->components.push_back(component);
}
void Object3D::OnStart() {

}

void Object3D::Enable() {
    for(int i=0; i<components.size(); i++) {
        components[i]->OnEnable();
    }
}

Component* Object3D::GetComponent(std::string name) {
	for(int i=0; i<components.size(); i++) { 
		if(components[i]->name == name) {
			return components[i];
		}
	}
}

void Object3D::Render() {
	GETGL
	//GET MODEL MATRIX FROM TRANSFORM COMPONENT
	TransformComponent* transform = (TransformComponent*)(this->GetComponent("Transform")); 
	glm::mat4 mMatrix = transform->GetModelMatrix();
	
	// glm::mat4 mMatrix = glm::mat4(1.0);
	glm::mat4 vMatrix = scene->camera.GetViewMatrix();
	glm::mat4 pMatrix = scene->camera.GetProjectionMatrix();
	glm::mat4 mvpMatrix = pMatrix * vMatrix * mMatrix;


	//
	//Set GL states
	//
	//disable writting to depth buffer
	ogl->glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	
	//enable blending
	ogl->glEnable(GL_BLEND);
	ogl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//
	//update shader state and bind
	//
	
	//IF NO MATERIAL COMPONENT : STANDARD SHADER
	//bind shader

	// Shader s = scene->standardShaders.unlitMeshShader;
	ogl->glUseProgram(shader.programShaderObject);
	
	//update mvp transform uniform in shader
	int modelViewProjectionMatrixLocation = ogl->glGetUniformLocation(shader.programShaderObject, "modelViewProjectionMatrix"); 
	ogl->glUniformMatrix4fv(modelViewProjectionMatrixLocation, 1, false, glm::value_ptr(mvpMatrix));
	
	int modelMatrixLocation = ogl->glGetUniformLocation(shader.programShaderObject, "modelMatrix"); 
	ogl->glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(mMatrix));

	
	//materialColor
	// ogl->glUniform4f(ogl->glGetUniformLocation(scene->standardShaders.lineShader.programShaderObject, "materialColor"), 1, 1, 1, 1);

	//
	//Draw
	//
    for(int i=0; i<components.size(); i++) {
        components[i]->OnRender();
    }    
	
	//
	//unbind shader
	//
	
	//unbind shader program
	ogl->glUseProgram(0);    


}
}
}