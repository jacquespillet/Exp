#include "Scene_7.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"
#include "3DEngine/BaseObjects.hpp"

#include "View3D/View3DGL.hpp"

#include "Common/QtWidgets.hpp"
#include "Common/ModelLoader.hpp"

#include "ObjectShader.hpp"
#include "QuadShader.hpp"
#include "LightShader.hpp"

#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_7_ {

void Scene_7::OnStart(){

    CustomSlider* sigmaSlider = new CustomSlider(-10, 10, 0.01, "sigma", sigma);
    parentWidget->optionsWidget->layout()->addWidget(sigmaSlider);
    QObject::connect(sigmaSlider, &CustomSlider::Modified, [this, sigmaSlider](double val) {
        sigma = val;
    });
    CustomSlider* lightIntSlider = new CustomSlider(0, 10, 0.01, "lightInt", lightInt);
    parentWidget->optionsWidget->layout()->addWidget(lightIntSlider);
    QObject::connect(lightIntSlider, &CustomSlider::Modified, [this, lightIntSlider](double val) {
        lightInt = val;
    });
    
    parentWidget->optionsWidget->show();


    camera = new CoreEngine::CameraScene(this, 1.0, glm::radians(70.0f), 0.1, 1000.0, 1.0);
    camera->transform->position = glm::vec3(0, 1, -2);
    camera->transform->rotation.x = 10.0f;

    
    lightPos = glm::vec3(0, 0, 2);
    virtualCamera = new CoreEngine::CameraScene(this, 1.0, 70.0f, 0.1, 5.0, 1.0);
    virtualCamera->SetProjectionMatrix(glm::orthoLH(-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f));
    virtualCamera->transform->position = lightPos;
    virtualCamera->transform->rotation.y = 180;

    depthFb = new CoreEngine::Framebuffer(2048, 2048, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, true, true);
    
    dragon = FileIO::ObjectFromFile("res/Models/dragon/dragon.obj", this, GetObjectShader());
    dragon->transform->rotation.y = 90;
    dragon->Enable();
    dragon->shader.shouldRecompile=false;

    lightShader = GetLightShader();
    dragonShader = dragon->shader;


    quad = GetQuad(this, "quad", glm::vec3(0), glm::vec3(0), glm::vec3(1), glm::vec4(1), GetQuadShader());
    quad->Enable();
}

void Scene_7::OnDestroy() {
    delete dragon;
    delete depthFb;
}

void Scene_7::OnRender() {
    GETGL
    _time += deltaTime;

    //Light pass
    {
        ogl->glViewport(0, 0, 2048, 2048);
        //Render scene from camera pov onto fbo
        depthFb->Enable();        
        ogl->glClearColor(1, 0.5, 0.5, 1);
        ogl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Render scene
        CoreEngine::CameraScene* tmp = camera;
        this->camera = virtualCamera;
        dragon->shader = lightShader;
        dragon->Render();
        this->camera = tmp;
        
        depthFb->Disable();      
        ogl->glViewport(0, 0, windowWidth, windowHeight);  
        

        // //Render quad
        ogl->glUseProgram(quad->shader.programShaderObject);
        Texture depthMap;
        // depthMap.glTex = depthFb->textures[0];
        depthMap.glTex = depthFb->depthTexture;
        depthMap.texIndex = GL_TEXTURE0;
        depthMap.Use();
        int texLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, "depthMap");
        ogl->glUniform1i(texLocation, 0);        
        quad->Render();
    }
  
    //Object pass
    {
        dragon->shader = dragonShader;
        Texture depthMap;
        ogl->glUseProgram(dragon->shader.programShaderObject);
        depthMap.glTex = depthFb->depthTexture;
        depthMap.texIndex = GL_TEXTURE0;
        depthMap.Use();
        int texLocation = ogl->glGetUniformLocation(dragon->shader.programShaderObject, "depthMap");
        ogl->glUniform1i(texLocation, 0);

        // virtualCamera->UpdateProjectionMatrix();
        // glm::mat4 lightMvp = virtualCamera->GetProjectionMatrix() * virtualCamera->GetViewMatrix() * dragon->transform->GetModelMatrix();
        glm::mat4 lightMvp = dragon->mvpMatrix;  
        ogl->glUniformMatrix4fv(ogl->glGetUniformLocation(dragon->shader.programShaderObject, "lightMvp"), 1, false, glm::value_ptr(lightMvp));  

        int eyePosLocation = ogl->glGetUniformLocation(dragon->shader.programShaderObject, "eyePos"); 
        ogl->glUniform3fv(eyePosLocation, 1, glm::value_ptr(glm::vec3(camera->transform->position)));           

        int lightPosLocation = ogl->glGetUniformLocation(dragon->shader.programShaderObject, "lightPos"); 
        ogl->glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));           

        int sigmaLocation = ogl->glGetUniformLocation(dragon->shader.programShaderObject, "sigma"); 
        ogl->glUniform1f(sigmaLocation, sigma);     

        int lightIntLocation = ogl->glGetUniformLocation(dragon->shader.programShaderObject, "lightInt"); 
        ogl->glUniform1f(lightIntLocation, lightInt);           

        dragon->Render();
    }
    
    triggerRefresh = true;
}

void Scene_7::OnUpdate() {
    camera->OnUpdate();
}

}
}