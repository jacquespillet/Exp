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

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();

    void SortAttributes();

    float _time;

    CoreEngine::Object3D* plane;
    
    float density = 1.5;
    int size = 100;
    int visibleNumber=0;

    CoreEngine::MeshFilterComponent* mesh;
    std::vector<CoreEngine::MeshFilterComponent::InstanceAttribute> instanceAttributes;
    std::vector<CoreEngine::MeshFilterComponent::InstanceAttribute> selectedInstanceAttributes;

    CoreEngine::Texture tex;
};

}
}