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
void Scene_5::OnStart(){
    camera = new CoreEngine::CameraScene(this, 1, 70.0f, 0.1, 1000.0, (float)windowWidth/(float)windowHeight);
    camera->transform->position = glm::vec3(0, 5, 0);
    camera->transform->rotation.x = glm::radians(10.0f);    
    bgColor = glm::vec3(0);

    {
        //Start each Object3D in scene
        plane = new Object3D("Triangle", this, GetGrassShader());
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec4> colors;
        std::vector<int> triangles;

        {
            vertex.push_back(glm::vec3(-1, 0, 0)); //bottom left
            vertex.push_back(glm::vec3(-1, 2, 0)); // top left
            vertex.push_back(glm::vec3( 1, 2, 0)); //Top right
            vertex.push_back(glm::vec3( 1, 0, 0)); //Bottom right

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
}

void Scene_5::OnDestroy() {
    delete plane;
}

void Scene_5::SortAttributes() {
    CoreEngine::MeshFilterComponent::InstanceAttribute key;
    int i, j;  
    for (i = 1; i < visibleNumber; i++) 
    {  
        key = instanceAttributes[i];  
        j = i - 1;
  
        while (j >= 0 && instanceAttributes[j].additionalData1.z < key.additionalData1.z) 
        {  
            instanceAttributes[j + 1] = instanceAttributes[j];  
            j = j - 1;  
        }  
        instanceAttributes[j + 1] = key;  
    }     
}


float map(float value, 
                              float istart, 
                              float istop, 
                              float ostart, 
                              float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}


void Scene_5::OnRender() {
    GETGL
    _time += deltaTime;   

    ogl->glClearColor(0.8, 0.8, 0.8, 1);
    
    ogl->glUseProgram(plane->shader.programShaderObject);
    
    int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
    ogl->glUniform1f(timeLocation, _time * 0.1);
    
    tex.Use();
    int tex = ogl->glGetUniformLocation(plane->shader.programShaderObject, "grassTex"); 
    ogl->glUniform1i(tex, 0);

    mesh->numInstances = size * size * density * density;
    
    if(instanceAttributes.size() != mesh->numInstances) instanceAttributes = std::vector<MeshFilterComponent::InstanceAttribute>(mesh->numInstances);
    float incr = 1.0 / density;
    float halfSize = size * 0.5;


    // std::cout << displacement << std::endl;
    visibleNumber=0;
    glm::vec3 camForward = glm::vec3(glm::column(camera->transform->GetModelMatrix(), 2));
    glm::vec3 camPos = glm::vec3(camera->transform->position);
    glm::mat4 vMatrix = camera->GetViewMatrix();
    glm::mat4 pMatrix = camera->GetProjectionMatrix();
    std::srand(0);

    for(float z=0; z<size; z+=incr) {
        for(float x=0; x<size; x+=incr) {
            float dx = x +  0.4 * (((float)std::rand() / (float)RAND_MAX) - 0.5);
            float dz = z + 0.4 * (((float)std::rand() / (float)RAND_MAX) - 0.5);
            glm::vec3 toCam = glm::vec3(dx - halfSize, 0, dz-halfSize) - camPos;
            float distance = glm::length(toCam);
            distance = map(distance, 0, size, 0, 1);
            float prob = ((float)std::rand() / (float)RAND_MAX);

            if(visibleNumber >= instanceAttributes.size()-1) break;
            if(glm::dot(toCam, camForward)>0) {
                if(prob < 1 - distance) {
                    Noise n = PerlinNoise3D(glm::vec3(dx, dz, time * 0.0001), 1);
                    float displacementX = n.derivative.x * 0.5;
                    float displacementY = n.derivative.y * 0.5;
                    
                    // float y = n.value * 10;
                    float y = noise(glm::vec2(dx/size, dz/size) * 10) * 3;

                    plane->transform->position = glm::vec3(dx-halfSize, y, dz - halfSize);
                    plane->transform->scale = glm::vec3(1);
                    plane->transform->rotation = glm::vec3(0);

                    glm::mat4 mMatrix = plane->transform->GetModelMatrix();

                    glm::mat4 mvp = pMatrix * vMatrix *  mMatrix;

                    float distance = glm::distance(plane->transform->position, camera->transform->position);

                    instanceAttributes[visibleNumber].modelMatrix = mvp;
                    instanceAttributes[visibleNumber].additionalData1 = glm::vec4(displacementX, displacementY, distance, 0);
                    instanceAttributes[visibleNumber].additionalData2 = glm::vec4(displacementY);

                    visibleNumber++;
                }
            }
        }
    }
  
    std::cout << visibleNumber << "  " << instanceAttributes.size() << std::endl;
    SortAttributes();
    mesh->numInstances = visibleNumber;
    mesh->SetInstanceAttributes(instanceAttributes);

    //Speed up : only sort what is in front of me, change the number of instances based on that number



    plane->Render();     
}

void Scene_5::OnUpdate() {
    camera->OnUpdate();
}

}
}