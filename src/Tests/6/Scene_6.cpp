#include "Scene_6.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"
#include "DiffractionShader.hpp"

#include "Common/QtWidgets.hpp"
#include "View3D/View3DGL.hpp"
#include "3DEngine/BaseObjects.hpp"

#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_6_ {

void Scene_6::OnStart(){
    CustomSlider* roughnessSlider = new CustomSlider(0, 3, 0.001, "roughness", roughness);
    parentWidget->optionsWidget->layout()->addWidget(roughnessSlider);
    QObject::connect(roughnessSlider, &CustomSlider::Modified, [this, roughnessSlider](double val) {
        roughness = val;
    });
    
    CustomSlider* dSlider = new CustomSlider(0, 3, 0.001, "d", d);
    parentWidget->optionsWidget->layout()->addWidget(dSlider);
    QObject::connect(dSlider, &CustomSlider::Modified, [this, dSlider](double val) {
        d = val;
    });

    parentWidget->optionsWidget->show();

    camera = new CameraScene(this, 1.0, glm::radians(70.0f), 0.1, 1000.0, 1.0);
    camera->transform->position = glm::vec3(0, 1, -2);
    camera->transform->rotation.x = glm::radians(10.0f);

    {
        //Start each Object3D in scene
        disc = new Object3D("Triangle", this, GetDiffractionShader());
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec4> colors;
        std::vector<int> triangles;
        
        vertex.push_back(glm::vec3(-0.5, 0, -0.5)); //bottom left
        vertex.push_back(glm::vec3(-0.5, 0,  0.5)); // top left
        vertex.push_back(glm::vec3( 0.5, 0,  0.5)); //Top right
        vertex.push_back(glm::vec3( 0.5, 0, -0.5)); //Bottom right

        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 1));
        uv.push_back(glm::vec2(1, 1));
        uv.push_back(glm::vec2(1, 0));

        colors.push_back(glm::vec4(255, 255, 255, 255));
        colors.push_back(glm::vec4(255, 255, 255, 255));
        colors.push_back(glm::vec4(255, 255, 255, 255));
        colors.push_back(glm::vec4(255, 255, 255, 255));

        int index = 0;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);

        MeshFilterComponent* mesh = new MeshFilterComponent();
        mesh->LoadFromBuffers( vertex, normals, uv, colors, triangles);
        TransformComponent* transform = new TransformComponent();
        
        disc->AddComponent(mesh);
        disc->transform = transform;

        disc->Enable();
    }
  
    skyboxCube = GetCube(this, "Cubemap", glm::vec3(0), glm::vec3(0), glm::vec3(100), glm::vec4(0.1, 0.1, 0.1, 1), standardShaders.unlitMeshShader);
    skyboxCube->Enable();        

    SetSkybox(std::vector<std::string> {
        "C:/Users/GYFLYM/Pictures/sky/chapel/posx.jpg",
        "C:/Users/GYFLYM/Pictures/sky/chapel/negx.jpg",
        "C:/Users/GYFLYM/Pictures/sky/chapel/posy.jpg",
        "C:/Users/GYFLYM/Pictures/sky/chapel/negy.jpg",
        "C:/Users/GYFLYM/Pictures/sky/chapel/posz.jpg",
        "C:/Users/GYFLYM/Pictures/sky/chapel/negz.jpg"
    });
}

void Scene_6::OnDestroy() {
    delete disc;
}

void Scene_6::OnRender() {
    GETGL
    _time += deltaTime;
    
    ogl->glUseProgram(disc->shader.programShaderObject);
    
    int eyePosLocation = ogl->glGetUniformLocation(disc->shader.programShaderObject, "eyePos"); 
    ogl->glUniform3fv(eyePosLocation, 1, glm::value_ptr(glm::vec3(camera->transform->position)));      

    int roughnessLocation = ogl->glGetUniformLocation(disc->shader.programShaderObject, "r"); 
    ogl->glUniform1f(roughnessLocation, roughness);        

    int dLocation = ogl->glGetUniformLocation(disc->shader.programShaderObject, "d"); 
    ogl->glUniform1f(dLocation, d);        

    disc->Render();

    triggerRefresh = true;
}

void Scene_6::OnUpdate() {
}

}
}