#pragma once
#include "Common/Common.h"
// #include "Component.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

namespace KikooRenderer {

namespace CoreEngine {
class Component;
class TransformComponent;
class Scene;
class Object3D {
    public: 
        std::string name;
        std::vector<Component*> components;
        Scene* scene;

        Shader shader;

        bool visible;
        bool enabled;

        TransformComponent* transform;
        glm::mat4 mvpMatrix;

        Object3D(std::string name, Scene* scene, Shader _shader);
        void AddComponent(Component* component);
        Component*  GetComponent(std::string name);

        void OnStart();
        void Enable();
        void Render();
        void Destroy();
};
}

}