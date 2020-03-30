#include "Scene_1.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"

#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_1_ {
void Scene_1::OnStart() {
    camera = new CameraScene(this, 1.0, glm::radians(70.0f), 0.1, 1000.0, 1.0);
    camera->transform->position = glm::vec3(0, 10, -15);
    camera->transform->rotation.x = glm::radians(10.0f);

    {
        //Start each Object3D in scene
        plane = new Object3D("Triangle", this, GetShader());
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec4> colors;
        std::vector<int> triangles;

        float width=10;
        float height=10;
        int subdivisionsX=1000; 
        int subdivisionsY=1000;

        float xOffset = width / (float)subdivisionsX;
        float yOffset = height / (float)subdivisionsY;
  
        //
        ///Vertices
        //
        int numAdded=0;
        for(float y=0, yInx=0; yInx<subdivisionsY; y+=yOffset, yInx++) {
            for(float x=0, xInx=0; xInx<subdivisionsX; x+= xOffset, xInx++) {
                vertex.push_back(glm::vec3(x, 0, y));
                normals.push_back(glm::vec3(0, 1, 0));
                uv.push_back(glm::vec2(xInx / (float) subdivisionsX, yInx / (float) subdivisionsY));
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
        plane->transform = transform;
        plane->Enable();

        // objects3D.push_back(plane);
    }

    {
        //Start each Object3D in scene
        quad = new Object3D("Triangle", this, GetTextureShader());
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec4> colors;
        std::vector<int> triangles;
        
        vertex.push_back(glm::vec3(-1.0, -1.0, 0.1)); //bottom left
        vertex.push_back(glm::vec3(-1.0, 1.0, 0.1)); // top left
        vertex.push_back(glm::vec3(1.0, 1.0, 0.1)); //Top right
        vertex.push_back(glm::vec3(1.0, -1.0, 0.1)); //Bottom right

        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        
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

        MeshFilterComponent* mesh = new MeshFilterComponent();
        mesh->LoadFromBuffers( vertex, normals, uv, colors, triangles);
        TransformComponent* transform = new TransformComponent();
        
        quad->AddComponent(mesh);
        quad->transform = transform;

        quad->Enable();

        fb = new Framebuffer(1200, 1200, GL_RGB32F, GL_RGB, GL_FLOAT, true, false, false);
    }
    {
        vNumWaves = 5;
        vWaveLengthMedian = 2;
        vAmplitudesMedian = 0.3;
        
        // float AOverW = vAmplitudesMedian / vWaveLengthMedian;
        for(int i=0; i<vNumWaves; i++) {
            float waveLength = GetRand(vWaveLengthMedian, 1);
            float amplitude = GetRand(vAmplitudesMedian, 0.1);

            vWaveLengths.push_back(waveLength);
            vAmplitudes.push_back(amplitude);
            vSpeeds.push_back(GetRandBtw(0.6, 3));
            vqs.push_back(GetRandBtw(0.3, 1));
            vDirections.push_back(glm::normalize(glm::vec2(GetRandBtw(0, 1), GetRandBtw(0, 1))));
        }
    }

    {
        tNumWaves = 5;
        tWaveLengthMedian = 5;
        tAmplitudesMedian = 0.08;
        
        // float AOverW = vAmplitudesMedian / vWaveLengthMedian;
        for(int i=0; i<tNumWaves; i++) {
            float waveLength = GetRand(tWaveLengthMedian, 3); 
            float amplitude = GetRand(tAmplitudesMedian, 0.04);

            tWaveLengths.push_back(waveLength);
            tAmplitudes.push_back(amplitude);
            tSpeeds.push_back(1);
            tqs.push_back(GetRandBtw(0.3, 1));
            
            tDirections.push_back(glm::normalize(tDirectionsMedian + glm::vec2(GetRandBtw(0, 0.4), GetRandBtw(0, 0.4))));
        }
    }

}

void Scene_1::OnDestroy() {
    delete fb;
    delete plane;
    delete quad;
}

void Scene_1::OnRender() {
    GETGL
    _time += deltaTime;
    {
        fb->Enable();        
        ogl->glClearColor(0, 0, 0, 1);
        ogl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ogl->glUseProgram(quad->shader.programShaderObject);
        
        int timeLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, "time"); 
        ogl->glUniform1f(timeLocation, _time);

        int numWavesLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, "numWaves"); 
        ogl->glUniform1i(numWavesLocation, tNumWaves);
        for(int i=0; i<tNumWaves; i++) {
            std::string varName = "waveLengths[" + std::to_string(i) + "]";
            int waveLengthLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(waveLengthLocation, tWaveLengths[i]);
            
            varName = "amplitudes[" + std::to_string(i) + "]";
            int amplitudesLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(amplitudesLocation, tAmplitudes[i]);
            
            varName = "speeds[" + std::to_string(i) + "]";
            int speedsLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(speedsLocation, tSpeeds[i]);
            
            varName = "qs[" + std::to_string(i) + "]";
            int qsLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(qsLocation, tqs[i]);

            varName = "directions[" + std::to_string(i) + "]";
            int directionLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform2fv(directionLocation, 1, glm::value_ptr(tDirections[i]));
        }    

        quad->Render();
        fb->Disable();
    }
    
    {
        ogl->glUseProgram(plane->shader.programShaderObject);

        Texture albedoTex;
        albedoTex.glTex = fb->textures[0];
        albedoTex.loaded = true;
        albedoTex.texIndex = GL_TEXTURE0;
        albedoTex.Use();

        int numWavesLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "numWaves"); 
        ogl->glUniform1i(numWavesLocation, vNumWaves);
        for(int i=0; i<vNumWaves; i++) {
            std::string varName = "waveLengths[" + std::to_string(i) + "]";
            int waveLengthLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(waveLengthLocation, vWaveLengths[i]);
            
            varName = "amplitudes[" + std::to_string(i) + "]";
            int amplitudesLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(amplitudesLocation, vAmplitudes[i]);

            varName = "speeds[" + std::to_string(i) + "]";
            int speedsLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(speedsLocation, vSpeeds[i]);
            
            varName = "qs[" + std::to_string(i) + "]";
            int qsLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(qsLocation, vqs[i]);

            varName = "directions[" + std::to_string(i) + "]";
            int directionLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform2fv(directionLocation, 1, glm::value_ptr(vDirections[i]));
        }
        
        int texLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "albedoTexture");
        ogl->glUniform1i(texLocation, 0);

        int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
        ogl->glUniform1f(timeLocation, _time);

        int eyePosLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "eyePos"); 
        ogl->glUniform3fv(eyePosLocation, 1, glm::value_ptr(glm::vec3(camera->transform->position)));
        
        plane->Render();
    }
    triggerRefresh = true;
}

void Scene_1::OnUpdate() {
}

}
}