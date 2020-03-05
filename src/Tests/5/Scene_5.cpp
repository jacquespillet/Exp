#include "Scene_5.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"
#include "View3D/View3DGL.hpp"
#include "Common/QtWidgets.hpp"
#include "GrassShader.hpp"

#include "Noise.hpp"

#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_5_ {
void Scene_5::Start(){
    OnStart();
    camera = new CoreEngine::CameraScene(this, 1, 70.0f, 0.1, 1000.0, (float)windowWidth/(float)windowHeight);
    camera->transform->position = glm::vec3(0, 10, -15);
    camera->transform->rotation.x = glm::radians(10.0f);    

    {
        //Start each Object3D in scene
        plane = new Object3D("Triangle", this, GetGrassShader());
        std::vector<glm::dvec3> vertex;
        std::vector<glm::dvec3> normals;
        std::vector<glm::dvec2> uv;
        std::vector<glm::dvec4> colors;
        std::vector<int> triangles;

        {
            vertex.push_back(glm::vec3(-1,-1, 0)); //bottom left
            vertex.push_back(glm::vec3(-1, 1, 0)); // top left
            vertex.push_back(glm::vec3( 1, 1, 0)); //Top right
            vertex.push_back(glm::vec3( 1,-1, 0)); //Bottom right

            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            
            uv.push_back(glm::vec2(0, 0));
            uv.push_back(glm::vec2(0, 1));
            uv.push_back(glm::vec2(1, 1));
            uv.push_back(glm::vec2(1, 0));

            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));

            int index = 0;
            triangles.push_back(index + 0);
            triangles.push_back(index + 2);
            triangles.push_back(index + 1);
            triangles.push_back(index + 3);
            triangles.push_back(index + 2);
            triangles.push_back(index + 0);
        }

        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1), 45.0f, glm::vec3(0, 1, 0));
            vertex.push_back(glm::vec3(rotation * glm::vec4(-1,-1, 0, 1))); //bottom left
            vertex.push_back(glm::vec3(rotation * glm::vec4(-1, 1, 0, 1))); // top left
            vertex.push_back(glm::vec3(rotation * glm::vec4( 1, 1, 0, 1))); //Top right
            vertex.push_back(glm::vec3(rotation * glm::vec4( 1,-1, 0, 1))); //Bottom right

            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            
            uv.push_back(glm::vec2(0, 0));
            uv.push_back(glm::vec2(0, 1));
            uv.push_back(glm::vec2(1, 1));
            uv.push_back(glm::vec2(1, 0));

            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));

            int index = 4;
            triangles.push_back(index + 0);
            triangles.push_back(index + 2);
            triangles.push_back(index + 1);
            triangles.push_back(index + 3);
            triangles.push_back(index + 2);
            triangles.push_back(index + 0);
        }

        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1), -45.0f, glm::vec3(0, 1, 0));
            vertex.push_back(glm::vec3(rotation * glm::vec4(-1,-1, 0, 1))); //bottom left
            vertex.push_back(glm::vec3(rotation * glm::vec4(-1, 1, 0, 1))); // top left
            vertex.push_back(glm::vec3(rotation * glm::vec4( 1, 1, 0, 1))); //Top right
            vertex.push_back(glm::vec3(rotation * glm::vec4( 1,-1, 0, 1))); //Bottom right

            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            normals.push_back(glm::vec3(0, 1, 0));
            
            uv.push_back(glm::vec2(0, 0));
            uv.push_back(glm::vec2(0, 1));
            uv.push_back(glm::vec2(1, 1));
            uv.push_back(glm::vec2(1, 0));

            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));
            colors.push_back(glm::vec4(255, 255, 255, 255));

            int index = 8;
            triangles.push_back(index + 0);
            triangles.push_back(index + 2);
            triangles.push_back(index + 1);
            triangles.push_back(index + 3);
            triangles.push_back(index + 2);
            triangles.push_back(index + 0);
        }
        

        mesh = new MeshFilterComponent();
        mesh->LoadFromBuffers( vertex, normals, uv, colors, triangles);
        TransformComponent* transform = new TransformComponent();
        
        plane->AddComponent(mesh);
        plane->transform = transform;

        mesh->renderInstanced = true;
        mesh->numInstances = size * size;

        plane->Enable();
    }
    tex = Texture("res/5/grass.png", GL_TEXTURE0, true);

    this->started = true;
}

void Scene_5::OnDestroy() {
    delete plane;
}

void Scene_5::OnRender() {
    GETGL
    _time += deltaTime;   

    ogl->glUseProgram(plane->shader.programShaderObject);
    
    int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
    ogl->glUniform1f(timeLocation, _time * 0.1);
    
    tex.Use();
    int tex = ogl->glGetUniformLocation(plane->shader.programShaderObject, "grassTex"); 
    ogl->glUniform1i(tex, 0);

    mesh->numInstances = size * size;
    instanceAttributes = std::vector<MeshFilterComponent::InstanceAttribute>(size * size);
    
    float incr = 1;
    for(float y=0, inx =0; y<size; y+=incr) {
        for(float x=0; x<size; x+=incr, inx++) {
            plane->transform->position = glm::vec3(x, 0, y);
            instanceAttributes[inx].modelMatrix = plane->transform->GetModelMatrix();
        }
    }
    mesh->SetInstanceAttributes(instanceAttributes);



    plane->Render();     
}

void Scene_5::OnUpdate() {
}

}
}