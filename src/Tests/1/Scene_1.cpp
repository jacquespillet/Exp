#include "Scene_1.hpp"

#include <QOpenGLFunctions_3_2_Core>
#define GLV QOpenGLFunctions_3_2_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace CoreEngine {
void Scene_1::Start() {
    this->started = true;
    OnStart();

    camera.transform.position = glm::vec3(0, 5, -10);

    //Start each Object3D in scene
    plane = new Object3D("Triangle", this, GetShader());
    std::vector<glm::dvec3> vertex;
    std::vector<glm::dvec3> normals;
    std::vector<glm::dvec2> uv;
    std::vector<glm::dvec4> colors;
    std::vector<int> triangles;

    float width=10;
    float height=10;
    int subdivisionsX=100; 
    int subdivisionsY=100;

    float xOffset = width / (float)subdivisionsX;
    float yOffset = height / (float)subdivisionsY;

    //
    ///Vertices
    //
    int numAdded=0;
    for(float y=-width/2, yInx=0; yInx<subdivisionsY; y+=yOffset, yInx++) {
        for(float x=-height/2, xInx=0; xInx<subdivisionsX; x+= xOffset, xInx++) {
            vertex.push_back(glm::vec3(x, 0, y));
            normals.push_back(glm::vec3(0, 1, 0));
            uv.push_back(glm::vec2(0, 0));
            colors.push_back(glm::vec4(255, 255, 255, 255));  

            if(xInx < subdivisionsX-1 && yInx < subdivisionsY-1) {
                triangles.push_back(numAdded);
                triangles.push_back(numAdded + subdivisionsX + 1);
                triangles.push_back(numAdded + subdivisionsX);
                
                triangles.push_back(numAdded);
                triangles.push_back(numAdded + 1);
                triangles.push_back(numAdded + subdivisionsX + 1);
            }
            numAdded++;
        }
    }
    

    MeshFilterComponent* mesh = new MeshFilterComponent();
    mesh->LoadFromBuffers( vertex, normals, uv, colors, triangles);
    TransformComponent* transform = new TransformComponent();
    
    plane->AddComponent(mesh);
    plane->AddComponent(transform);

    objects3D.push_back(plane);
}


void Scene_1::OnUpdate() {
    GETGL
    ogl->glUseProgram(plane->shader.programShaderObject);
	int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
	ogl->glUniform1f(timeLocation, time / CLOCKS_PER_SEC);

	int eyePosLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "eyePos"); 
	ogl->glUniform3fv(eyePosLocation, 1, glm::value_ptr(glm::vec3(camera.transform.position)));
	

    triggerRefresh = true;
}

}
}