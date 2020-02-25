#include "Scene_2.hpp"
#include "3DEngine/TransformComponent.hpp"
#include "3DEngine/CameraScene.hpp"

#include <QOpenGLFunctions_3_2_Core>
#define GLV QOpenGLFunctions_3_2_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace Scene_2_ {
void Scene_2::Start() {
    this->started = true;
    OnStart();

    camera = new CameraScene(this, 1.0, glm::radians(70.0f), 0.1, 1000.0, 1.0);
    camera->transform->position = glm::vec3(0, 10, -15);
    camera->transform->rotation.x = glm::radians(10.0f);

    {
        //Start each Object3D in scene
        plane = new Object3D("Triangle", this, GetShader());
        std::vector<glm::dvec3> vertex;
        std::vector<glm::dvec3> normals;
        std::vector<glm::dvec2> uv;
        std::vector<glm::dvec4> colors;
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
        for(float y=-width/2, yInx=0; yInx<subdivisionsY; y+=yOffset, yInx++) {
            for(float x=-height/2, xInx=0; xInx<subdivisionsX; x+= xOffset, xInx++) {
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
        std::vector<glm::dvec3> vertex;
        std::vector<glm::dvec3> normals;
        std::vector<glm::dvec2> uv;
        std::vector<glm::dvec4> colors;
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

        fb0 = new Framebuffer(1200, 1200, GL_RGB, GL_RGB, GL_FLOAT, true, false, false);
        fb1 = new Framebuffer(1200, 1200, GL_RGB, GL_RGB, GL_FLOAT, true, false, false);
    }    

    {
        //Start each Object3D in scene
        ground = new Object3D("Triangle", this, GetGroundShader());
        std::vector<glm::dvec3> vertex;
        std::vector<glm::dvec3> normals;
        std::vector<glm::dvec2> uv;
        std::vector<glm::dvec4> colors;
        std::vector<int> triangles;
        
        vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); //bottom left
        vertex.push_back(glm::vec3(-0.5, 0.5,  0.5)); // top left
        vertex.push_back(glm::vec3( 0.5, 0.5,  0.5)); //Top right
        vertex.push_back(glm::vec3( 0.5, 0.5, -0.5)); //Bottom right

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
        
        ground->AddComponent(mesh);
        ground->transform = transform;

        ground->Enable();

        ground->transform->position.y = -5;
        ground->transform->scale = glm::vec3(10, 1, 10);
    }


    //wave settings
    {
        vNumWaves = 15;
        vWaveLengthMedian = 3;
        vAmplitudesMedian = 0.1;
        
        float AOverW = vAmplitudesMedian / vWaveLengthMedian;
        for(int i=0; i<vNumWaves; i++) {
            float waveLength = GetRand(vWaveLengthMedian, 1);

            vWaveLengths.push_back(waveLength);
            vAmplitudes.push_back(AOverW * waveLength);
            vSpeeds.push_back(GetRandBtw(0.6, 3));
            vqs.push_back(GetRandBtw(0.3, 1));
            vDirections.push_back(glm::normalize(glm::vec2(GetRandBtw(0.2, 1), GetRandBtw(0.2, 1))));
        }
    }

    // glm::vec3 refracted = glm::refract(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), 1.3f);
    // std::cout << glm::to_string(refracted) << std::endl;
}

void Scene_2::OnDestroy() {
    std::cout << "DESTROY" << std::endl;
    delete plane;
    delete ground;
    delete fb0;
    delete fb1;
    delete quad;
}

void Scene_2::OnRender() {
    GETGL
    _time += deltaTime;
    {
        fb0->Enable();        
        ogl->glClearColor(0, 0, 0, 1);
        ogl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ogl->glUseProgram(quad->shader.programShaderObject);
        
        int timeLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, "time"); 
        ogl->glUniform1f(timeLocation, _time);

        int numWavesLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, "numWaves"); 
        ogl->glUniform1i(numWavesLocation, vNumWaves);
        for(int i=0; i<vNumWaves; i++) {
            std::string varName = "waveLengths[" + std::to_string(i) + "]";
            int waveLengthLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(waveLengthLocation, vWaveLengths[i]);
            
            varName = "amplitudes[" + std::to_string(i) + "]";
            int amplitudesLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(amplitudesLocation, vAmplitudes[i]);
            
            varName = "speeds[" + std::to_string(i) + "]";
            int speedsLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(speedsLocation, vSpeeds[i]);
            
            varName = "qs[" + std::to_string(i) + "]";
            int qsLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform1f(qsLocation, vqs[i]);

            varName = "directions[" + std::to_string(i) + "]";
            int directionLocation = ogl->glGetUniformLocation(quad->shader.programShaderObject, varName.c_str()); 
            ogl->glUniform2fv(directionLocation, 1, glm::value_ptr(vDirections[i]));
        }

        quad->Render();
        fb0->Disable();
    }

    {
        ogl->glUseProgram(ground->shader.programShaderObject);

        Texture albedoTex;
        albedoTex.glTex = fb0->texture;
        albedoTex.loaded = true;
        albedoTex.texIndex = GL_TEXTURE0;
        albedoTex.Use();
        
        int texLocation = ogl->glGetUniformLocation(ground->shader.programShaderObject, "normalMap");
        ogl->glUniform1i(texLocation, 0);

        ground->Render();
    }

    // {
    //     ogl->glUseProgram(plane->shader.programShaderObject);

    //     int numWavesLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "numWaves"); 
    //     ogl->glUniform1i(numWavesLocation, vNumWaves);
    //     for(int i=0; i<vNumWaves; i++) {
    //         std::string varName = "waveLengths[" + std::to_string(i) + "]";
    //         int waveLengthLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
    //         ogl->glUniform1f(waveLengthLocation, vWaveLengths[i]);
            
    //         varName = "amplitudes[" + std::to_string(i) + "]";
    //         int amplitudesLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
    //         ogl->glUniform1f(amplitudesLocation, vAmplitudes[i]);

    //         varName = "speeds[" + std::to_string(i) + "]";
    //         int speedsLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
    //         ogl->glUniform1f(speedsLocation, vSpeeds[i]);
            
    //         varName = "qs[" + std::to_string(i) + "]";
    //         int qsLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
    //         ogl->glUniform1f(qsLocation, vqs[i]);

    //         varName = "directions[" + std::to_string(i) + "]";
    //         int directionLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, varName.c_str()); 
    //         ogl->glUniform2fv(directionLocation, 1, glm::value_ptr(vDirections[i]));
    //     }
        
    //     int texLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "albedoTexture");
    //     ogl->glUniform1i(texLocation, 0);

    //     int timeLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "time"); 
    //     ogl->glUniform1f(timeLocation, _time);

    //     int eyePosLocation = ogl->glGetUniformLocation(plane->shader.programShaderObject, "eyePos"); 
    //     ogl->glUniform3fv(eyePosLocation, 1, glm::value_ptr(glm::vec3(camera->transform->position)));
        
        // plane->Render();
    // }
    triggerRefresh = true;
}

void Scene_2::OnUpdate() {
}

}
}