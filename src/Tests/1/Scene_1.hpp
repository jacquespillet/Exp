#pragma once
#include "3DEngine/Scene.hpp"
#include "PlaneShader.hpp"
#include "TextureShader.hpp"
#include "3DEngine/Framebuffer.hpp"

namespace KikooRenderer {
namespace Scene_1_ {

class Scene_1 : public Scene {
public:
    Scene_1(){}

    void OnStart();
    void virtual OnUpdate();
    void virtual OnRender();
    void virtual OnDestroy();


    Object3D* plane;

    Framebuffer* fb;
    Object3D* quad;

    int vNumWaves = 0;
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

    int tNumWaves = 0;
    float tWaveLengthMedian = 100;
    glm::vec2 tDirectionsMedian = glm::vec2(1, 1);
    float tAmplitudesMedian = 0.1;
    float tqMedian = 0.1;
    float tSpeedMedian = 1;
    std::vector<float> tqs;
    std::vector<float> tWaveLengths;
    std::vector<float> tAmplitudes;
    std::vector<float> tSpeeds;
    std::vector<glm::vec2> tDirections;

    float _time=0;

};

}
}