#pragma once
#include "3DEngine/Scene.hpp"

#include "3DEngine/Framebuffer.hpp"

namespace KikooRenderer {


namespace Scene_7_ {
class Scene_7 : public CoreEngine::Scene {
public:
    Scene_7(){}

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();

    CoreEngine::Object3D* dragon;
    CoreEngine::Object3D* quad;
    CoreEngine::Framebuffer* depthFb;

    CoreEngine::CameraScene* virtualCamera;

    CoreEngine::Shader lightShader;
    CoreEngine::Shader dragonShader;

    float _time=0;

    glm::vec3 lightPos;
    glm::vec3 lightDir;

    float sigma = 1;
    float lightInt = 1;

};

}
}