#pragma once
#include "3DEngine/Scene.hpp"
#include "PlaneShader.hpp"

namespace KikooRenderer {
namespace CoreEngine {

class Scene_1 : public Scene {
   
   virtual void Start();
   void virtual OnUpdate();

    Object3D* plane;
};

}
}