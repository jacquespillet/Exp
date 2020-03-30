#pragma once
#include "3DEngine/Scene.hpp"

#include "3DEngine/Framebuffer.hpp"

namespace KikooRenderer {


namespace Scene_6_ {
class Scene_6 : public CoreEngine::Scene {
public:
    Scene_6(){}

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();


    CoreEngine::Object3D* disc;

    float _time=0;
    float roughness=1;
    float d=1;

};

}
}