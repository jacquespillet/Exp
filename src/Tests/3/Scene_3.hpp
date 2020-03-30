#pragma once
#include "3DEngine/Scene.hpp"
#include "3DEngine/Framebuffer.hpp"
#include "3DEngine/Object3D.hpp"

namespace KikooRenderer {
class View3DGL;

namespace Scene_3_ {

class Scene_3 : public CoreEngine::Scene {
public:
    Scene_3(){}

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();

    CoreEngine::Object3D* plane;


    float _time=0;

    float frequency = 10;
    int interpMode = 0;
    int dimension = 1;
    int noiseType=0;
};

}
}