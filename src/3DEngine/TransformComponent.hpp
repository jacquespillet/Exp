#pragma once 
#include "Common/Common.h"
#include "Component.hpp"

namespace KikooRenderer {
namespace CoreEngine {
class Component;
class TransformComponent : public Component {
    public: 
        TransformComponent();
        void OnStart();
        void OnEnable();
        void OnUpdate();
        void OnRender();

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 GetModelMatrix(); 

        bool hasChanged;
};
}
}