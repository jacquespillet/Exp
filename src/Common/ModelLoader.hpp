#pragma once

#include "Common/Common.h"
#include "3DEngine/Object3D.hpp"

namespace KikooRenderer{
namespace FileIO {
    
    void GetModelBuffers(std::string filename, std::vector<glm::vec3>* vertex, std::vector<glm::vec3>* normals, std::vector<glm::vec2>* uv, std::vector<glm::vec4>* colors, std::vector<int>* triangles);

    void LoadModel(std::string filename, std::vector<glm::vec3>* vertex, std::vector<glm::vec3>* normals, std::vector<glm::vec2>* uv, std::vector<glm::vec4>* colors, std::vector<int>* triangles);

    CoreEngine::Object3D* ObjectFromFile(std::string filename, CoreEngine::Scene* s, CoreEngine::Shader shader);
}
}