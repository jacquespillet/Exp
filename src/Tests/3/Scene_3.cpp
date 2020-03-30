#include "Scene_3.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"
#include "View3D/View3DGL.hpp"
#include "PerlinShader.hpp"

#include "Common/QtWidgets.hpp"

#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_3_ {
void Scene_3::OnStart(){

    RadioGroup* dimensionRadioGroup = new RadioGroup("Dimensions", 4, 0);
    dimensionRadioGroup->AddButton("1", 1);
    dimensionRadioGroup->AddButton("2", 2);
    dimensionRadioGroup->AddButton("3", 3);
    dimensionRadioGroup->SetValue(1);
    parentWidget->optionsWidget->layout()->addWidget(dimensionRadioGroup);
    QObject::connect(dimensionRadioGroup, &RadioGroup::Modified, [this, dimensionRadioGroup]() {
        dimension = dimensionRadioGroup->GetValue();
    });

    RadioGroup* interpModeRadioGroup = new RadioGroup("Interpolation Mode", 3, 0);
    interpModeRadioGroup->AddButton("1 degree", 0);
    interpModeRadioGroup->AddButton("3 degrees", 1);
    interpModeRadioGroup->AddButton("6 degrees", 2);
    interpModeRadioGroup->SetValue(0);
    parentWidget->optionsWidget->layout()->addWidget(interpModeRadioGroup);
    QObject::connect(interpModeRadioGroup, &RadioGroup::Modified, [this, interpModeRadioGroup]() {
        interpMode = interpModeRadioGroup->GetValue();
    });

    RadioGroup* noiseTypeRadioGroup = new RadioGroup("Noise type", 3, 0);
    noiseTypeRadioGroup->AddButton("Value", 0);
    noiseTypeRadioGroup->AddButton("Perlin", 1);
    noiseTypeRadioGroup->AddButton("Simplex", 2);
    noiseTypeRadioGroup->SetValue(0);
    parentWidget->optionsWidget->layout()->addWidget(noiseTypeRadioGroup);
    QObject::connect(noiseTypeRadioGroup, &RadioGroup::Modified, [this, noiseTypeRadioGroup]() {
        noiseType = noiseTypeRadioGroup->GetValue();
    });

    CustomSlider* frequencySlider = new CustomSlider(1, 100, 0.5, "Frequency", 10);
    parentWidget->optionsWidget->layout()->addWidget(frequencySlider);
    QObject::connect(frequencySlider, &CustomSlider::Modified, [this, frequencySlider](double val) {
        frequency = val;
    });


    parentWidget->optionsWidget->show();


    camera = new CameraScene(this, 1.0, glm::radians(70.0f), 0.1, 1000.0, 1.0);
    camera->transform->position = glm::vec3(0, 10, -15);
    camera->transform->rotation.x = glm::radians(10.0f);    

    {
        //Start each Object3D in scene
        plane = new Object3D("Triangle", this, GetPerlinShader());
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec4> colors;
        std::vector<int> triangles;
        
        vertex.push_back(glm::vec3(-0.5,-0.5, 0.5)); //bottom left
        vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); // top left
        vertex.push_back(glm::vec3( 0.5, 0.5, 0.5)); //Top right
        vertex.push_back(glm::vec3( 0.5,-0.5, 0.5)); //Bottom right

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
        
        plane->AddComponent(mesh);
        plane->transform = transform;

        plane->Enable();

        plane->transform->scale = glm::vec3(10, 10, 0);
    }

}

void Scene_3::OnDestroy() {
    delete plane;
}

void Scene_3::OnRender() {
    GETGL
    _time += deltaTime;    
    
    ogl->glUseProgram(plane->shader.programShaderObject);
    
    int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
    ogl->glUniform1f(timeLocation, _time * 0.1);

    int frequencyLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "frequency"); 
    ogl->glUniform1f(frequencyLocation, frequency);
    
    int interpModeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "interpMode"); 
    ogl->glUniform1i(interpModeLocation, interpMode);

    int noiseTypeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "noiseType"); 
    ogl->glUniform1i(noiseTypeLocation, noiseType);

    int dimensionLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "dimension"); 
    ogl->glUniform1i(dimensionLocation, dimension);

    plane->Render();
}

void Scene_3::OnUpdate() {
}

}
}