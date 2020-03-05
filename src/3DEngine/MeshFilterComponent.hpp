#pragma once
#include "Common/Common.h"
#include "Component.hpp"

namespace KikooRenderer {
namespace CoreEngine {
class MeshFilterComponent : public Component {
    public:

		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;
			unsigned char r, g, b, a; 
		};    

        struct InstanceAttribute {
            glm::mat4 modelMatrix;
            glm::vec4 additionalData1;
            glm::vec4 additionalData2;
        };        

        MeshFilterComponent();
        void OnStart();
        void OnEnable();
        void OnUpdate();
        void OnRender();
        

        void LoadFromBuffers(std::vector<glm::dvec3> vertex,
        std::vector<glm::dvec3> normals,
        std::vector<glm::dvec2> uv,
        std::vector<glm::dvec4> colors,
        std::vector<int> triangles);
        void RebuildBuffers();

        void SetInstanceAttributes(std::vector<InstanceAttribute> modelMatrices);
        bool renderInstanced = false;
        int numInstances = 100;
        std::vector<InstanceAttribute> instanceAttributes;


    private: 
        void InitBuffers();

        std::vector<Vertex> vertices;
        std::vector<int> triangles;

        unsigned int vertexBuffer;
        unsigned int elementBuffer;
        unsigned int vertexArrayObject;
        
        unsigned int matricesBuffer;

};
}
}