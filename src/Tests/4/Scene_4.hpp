#pragma once
#include "3DEngine/Scene.hpp"
#include "3DEngine/Framebuffer.hpp"
#include "3DEngine/Object3D.hpp"

namespace KikooRenderer {
class View3DGL;

namespace Scene_4_ {

class Scene_4 : public CoreEngine::Scene {
public:
    Scene_4(){}

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();

    CoreEngine::Object3D* plane;


    float _time=0;

    float frequency = 20;
    int interpMode = 2;
    int dimension = 2;
    int noiseType=0;
    float glossiness = 32;
    float timeScale = 0.1;
};

}
}