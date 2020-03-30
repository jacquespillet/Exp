#pragma once

#include "Object3D.hpp"


namespace KikooRenderer {

namespace CoreEngine {

    Object3D* GetCube(Scene* scene, std::string name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, Shader shader, bool physics = false);
    Object3D* GetQuad(Scene* scene, std::string name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, Shader shader, bool physics = false);
    
}
}