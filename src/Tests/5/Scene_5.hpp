#pragma once
#include "3DEngine/Scene.hpp"
#include "3DEngine/Framebuffer.hpp"
#include "3DEngine/Object3D.hpp"
#include "3DEngine/MeshFilterComponent.hpp"

namespace KikooRenderer {
class View3DGL;


namespace Scene_5_ {

class Scene_5 : public CoreEngine::Scene {
public:
    Scene_5(){}

    void virtual Start();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();

    float _time;

    CoreEngine::Object3D* plane;
    
    float density = 1;
    int size = 10;

    CoreEngine::MeshFilterComponent* mesh;
    std::vector<CoreEngine::MeshFilterComponent::InstanceAttribute> instanceAttributes;

    CoreEngine::Texture tex;
};

}
}