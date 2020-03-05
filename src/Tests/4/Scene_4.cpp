#include "Scene_4.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"
#include "View3D/View3DGL.hpp"
#include "PerlinShader.hpp"

#include "Common/QtWidgets.hpp"

#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_4_ {
void Scene_4::Start(){

    RadioGroup* dimensionRadioGroup = new RadioGroup("Dimensions", 4, 0);
    dimensionRadioGroup->AddButton("1", 1);
    dimensionRadioGroup->AddButton("2", 2);
    dimensionRadioGroup->AddButton("3", 3);
    dimensionRadioGroup->SetValue(dimension);
    parentWidget->optionsWidget->layout()->addWidget(dimensionRadioGroup);
    QObject::connect(dimensionRadioGroup, &RadioGroup::Modified, [this, dimensionRadioGroup]() {
        dimension = dimensionRadioGroup->GetValue();
    });

    RadioGroup* interpModeRadioGroup = new RadioGroup("Interpolation Mode", 3, 0);
    interpModeRadioGroup->AddButton("1 degree", 0);
    interpModeRadioGroup->AddButton("3 degrees", 1);
    interpModeRadioGroup->AddButton("6 degrees", 2);
    interpModeRadioGroup->SetValue(interpMode);
    parentWidget->optionsWidget->layout()->addWidget(interpModeRadioGroup);
    QObject::connect(interpModeRadioGroup, &RadioGroup::Modified, [this, interpModeRadioGroup]() {
        interpMode = interpModeRadioGroup->GetValue();
    });

    RadioGroup* noiseTypeRadioGroup = new RadioGroup("Noise type", 3, 0);
    noiseTypeRadioGroup->AddButton("Value", 0);
    noiseTypeRadioGroup->AddButton("Perlin", 1);
    noiseTypeRadioGroup->AddButton("Simplex", 2);
    noiseTypeRadioGroup->SetValue(noiseType);
    parentWidget->optionsWidget->layout()->addWidget(noiseTypeRadioGroup);
    QObject::connect(noiseTypeRadioGroup, &RadioGroup::Modified, [this, noiseTypeRadioGroup]() {
        noiseType = noiseTypeRadioGroup->GetValue();
    });

    CustomSlider* frequencySlider = new CustomSlider(1, 100, 0.5, "Frequency", frequency);
    parentWidget->optionsWidget->layout()->addWidget(frequencySlider);
    QObject::connect(frequencySlider, &CustomSlider::Modified, [this, frequencySlider](double val) {
        frequency = val;
    });

    CustomSlider* glossinessSlider = new CustomSlider(24, 1024, 10, "glossiness", glossiness);
    parentWidget->optionsWidget->layout()->addWidget(glossinessSlider);
    QObject::connect(glossinessSlider, &CustomSlider::Modified, [this, glossinessSlider](double val) {
        glossiness = val;
    });

    CustomSlider* timeScaleSlider = new CustomSlider(0, 3, 0.01, "timeScale", timeScale);
    parentWidget->optionsWidget->layout()->addWidget(timeScaleSlider);
    QObject::connect(timeScaleSlider, &CustomSlider::Modified, [this, timeScaleSlider](double val) {
        timeScale = val;
    });


    parentWidget->optionsWidget->show();


    OnStart();

    camera = new CameraScene(this, 1.0, glm::radians(70.0f), 0.1, 1000.0, 1.0);
    camera->transform->position = glm::vec3(0, 10, -15);
    camera->transform->rotation.x = glm::radians(10.0f);    

    {
        //Start each Object3D in scene
        plane = new Object3D("Triangle", this, GetPerlinShader());
        std::vector<glm::dvec3> vertex;
        std::vector<glm::dvec3> normals;
        std::vector<glm::dvec2> uv;
        std::vector<glm::dvec4> colors;
        std::vector<int> triangles;
        
        vertex.push_back(glm::vec3(-1,-1, 0)); //bottom left
        vertex.push_back(glm::vec3(-1, 1, 0)); // top left
        vertex.push_back(glm::vec3( 1, 1, 0)); //Top right
        vertex.push_back(glm::vec3( 1,-1, 0)); //Bottom right

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

        // plane->transform->scale = glm::vec3(10, 10, 0);
    }


    this->started = true;
}

void Scene_4::OnDestroy() {
    delete plane;
}

void Scene_4::OnRender() {
    GETGL
    _time += deltaTime;    
    
    ogl->glUseProgram(plane->shader.programShaderObject);
    
    int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
    ogl->glUniform1f(timeLocation, _time * timeScale * (1 / frequency));

    int frequencyLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "frequency"); 
    ogl->glUniform1f(frequencyLocation, frequency);
    
    int interpModeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "interpMode"); 
    ogl->glUniform1i(interpModeLocation, interpMode);

    int noiseTypeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "noiseType"); 
    ogl->glUniform1i(noiseTypeLocation, noiseType);

    int dimensionLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "dimension"); 
    ogl->glUniform1i(dimensionLocation, dimension);

    ogl->glUniformMatrix4fv(ogl->glGetUniformLocation(plane->shader.programShaderObject, "camModelMatrix"), 1, false, glm::value_ptr(glm::mat4(camera->transform->GetModelMatrix())));  
    
    int camFovLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "camFov"); 
    ogl->glUniform1f(camFovLocation, camera->GetFov());
    
    int camAspectRatioLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "camAspectRatio"); 
    ogl->glUniform1f(camAspectRatioLocation, camera->GetAspect());

    int glossinessLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "glossiness"); 
    ogl->glUniform1f(glossinessLocation, glossiness);

    plane->Render();
}

void Scene_4::OnUpdate() {
}

}
}