#pragma once
#include "3DEngine/Scene.hpp"
#include "PlaneShader.hpp"
#include "GroundShader.hpp"
#include "TextureShader.hpp"
#include "3DEngine/Framebuffer.hpp"

namespace KikooRenderer {
namespace Scene_2_ {

class Scene_2 : public Scene {
public:
    Scene_2(){}

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();


    Object3D* plane;
    
    Object3D* ground;

    Framebuffer* fb0;
    Object3D* quad;

    Texture groundAlbedo;
    Texture groundNormal;

    int vNumWaves = 10;
    float vWaveLengthMedian = 3;
    glm::vec2 vDirectionsMedian = glm::vec2(1, 1);
    float vAmplitudesMedian = 0.1;
    float vqMedian = 0.1;
    float vSpeedMedian = 1;
    std::vector<float> vWaveLengths;
    std::vector<float> vAmplitudes;
    std::vector<float> vqs;
    std::vector<float> vSpeeds;
    std::vector<glm::vec2> vDirections;

    float _time=0;

};

}
}