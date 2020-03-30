#include "Scene.hpp"
#include "Util.hpp"
#include "CameraScene.hpp"
#include "TransformComponent.hpp"
#include "BaseObjects.hpp"
#include "View3D/View3DGL.hpp"

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {

namespace CoreEngine {
    Scene::Scene() {
        camera = new CameraScene(this, 1.0, 70 * Util::DEGTORAD, 0.1, 1000.0, 1.0);
        this->started = false;
    }

    void Scene::Start() {
        standardShaders.Compile();
        this->started = true;
        OnStart();
    }

    void Scene::OnStart() {

        //Start each Object3D in scene
        Object3D* newObject = new Object3D("Triangle", this, standardShaders.unlitMeshShader);
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec4> colors;
        std::vector<int> triangles;

        //
        ///Vertices
        //

        //Front
        vertex.push_back(glm::vec3(-0.5, -0.5, -0.5)); //bottom left
        vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); // top left
        vertex.push_back(glm::vec3(0.5, 0.5, -0.5)); //Top right
        vertex.push_back(glm::vec3(0.5, -0.5, -0.5)); //Bottom right

        // Back
        vertex.push_back(glm::vec3(0.5, -0.5, 0.5)); //Bottom Left
        vertex.push_back(glm::vec3(0.5, 0.5, 0.5)); //Top left
        vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); // top right
        vertex.push_back(glm::vec3(-0.5, -0.5, 0.5)); //bottom right

        // Right
        vertex.push_back(glm::vec3(0.5, -0.5, 0.5)); // Bottom left
        vertex.push_back(glm::vec3(0.5, 0.5, 0.5)); //Top left
        vertex.push_back(glm::vec3(0.5, 0.5, -0.5)); //Top right
        vertex.push_back(glm::vec3(0.5, -0.5, -0.5)); //Bottom right

        // Left
        vertex.push_back(glm::vec3(-0.5, -0.5, -0.5)); //Bottom Left
        vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); //Top left
        vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); //Top right
        vertex.push_back(glm::vec3(-0.5, -0.5, 0.5)); // Bottom right

        // Top
        vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); //Bottom Left
        vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); //Top Left
        vertex.push_back(glm::vec3(0.5, 0.5, -0.5)); // top right
        vertex.push_back(glm::vec3(0.5, 0.5, 0.5)); //bottom right

        // Bottom ?????
        vertex.push_back(glm::vec3( 0.5, -0.5,  0.5)); //bottom left
        vertex.push_back(glm::vec3( 0.5, -0.5, -0.5)); // top left
        vertex.push_back(glm::vec3(-0.5, -0.5, -0.5)); //Top right
        vertex.push_back(glm::vec3(-0.5, -0.5,  0.5)); //Bottom right


        //
        ///Normals
        //

        //Front
        normals.push_back(glm::vec3(0, 0, 1));
        normals.push_back(glm::vec3(0, 0, 1));
        normals.push_back(glm::vec3(0, 0, 1));
        normals.push_back(glm::vec3(0, 0, 1));
        
        //Back
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        normals.push_back(glm::vec3(0, 0, -1));
        
        //Right
        normals.push_back(glm::vec3(1, 0, 0));
        normals.push_back(glm::vec3(1, 0, 0));
        normals.push_back(glm::vec3(1, 0, 0));
        normals.push_back(glm::vec3(1, 0, 0));

        //Left
        normals.push_back(glm::vec3(-1, 0, 0));
        normals.push_back(glm::vec3(-1, 0, 0));
        normals.push_back(glm::vec3(-1, 0, 0));
        normals.push_back(glm::vec3(-1, 0, 0));
        
        //Top
        normals.push_back(glm::vec3(0, 1, 0));
        normals.push_back(glm::vec3(0, 1, 0));
        normals.push_back(glm::vec3(0, 1, 0));
        normals.push_back(glm::vec3(0, 1, 0));

        //Bottom
        normals.push_back(glm::vec3(0, -1, 0));
        normals.push_back(glm::vec3(0, -1, 0));
        normals.push_back(glm::vec3(0, -1, 0));
        normals.push_back(glm::vec3(0, -1, 0));


        //
        ////UV
        //

        //Front
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        
        //Back
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        
        //Right
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        
        //Left
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        
        //Top
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        
        //Bottom
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));
        uv.push_back(glm::vec2(0, 0));


        //
        ////Colors
        //

        //Front
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        colors.push_back(glm::vec4(0.0, 255, 0, 255));
        colors.push_back(glm::vec4(0.0, 0, 255, 255));
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        
        //Back
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        colors.push_back(glm::vec4(0.0, 255, 0, 255));
        colors.push_back(glm::vec4(0.0, 0, 255, 255));
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        
        //Right
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        colors.push_back(glm::vec4(0.0, 255, 0, 255));
        colors.push_back(glm::vec4(0.0, 0, 255, 255));
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        
        //Left
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        colors.push_back(glm::vec4(0.0, 255, 0, 255));
        colors.push_back(glm::vec4(0.0, 0, 255, 255));
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        
        //Top
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        colors.push_back(glm::vec4(0.0, 255, 0, 255));
        colors.push_back(glm::vec4(0.0, 0, 255, 255));
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        
        //Bottom
        colors.push_back(glm::vec4(255.0, 0, 0, 255));
        colors.push_back(glm::vec4(0.0, 255, 0, 255));
        colors.push_back(glm::vec4(0.0, 0, 255, 255));
        colors.push_back(glm::vec4(255.0, 0, 0, 255));


        //
        ////Triangles
        //

        //Front
        int index = 0;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);
        
        index = 4;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);

        index = 8;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);

        index = 12;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);

        index = 16;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);
        
        index = 20;
        triangles.push_back(index + 0);
        triangles.push_back(index + 2);
        triangles.push_back(index + 1);
        triangles.push_back(index + 3);
        triangles.push_back(index + 2);
        triangles.push_back(index + 0);

        MeshFilterComponent* mesh = new MeshFilterComponent();
        mesh->LoadFromBuffers( vertex, normals, uv, colors, triangles);
        TransformComponent* transform = new TransformComponent();
        
        newObject->AddComponent(mesh);
        newObject->transform = transform;

        objects3D.push_back(newObject);

    }

    void Scene::Enable() {
        OnEnable();
        //Enable each Object3D in scene
        for(int i=0; i<objects3D.size(); i++) {
            objects3D[i]->Enable();
        }
    }
    
    void Scene::OnUpdate() {

    }

    void Scene::Render() {
        GETGL
        ogl->glClearColor(bgColor.x, bgColor.y, bgColor.z, 1);
        ogl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(hasSkybox) skyboxCube->Render();
        
        OnRender();
        //Render each object
        for(int i=0; i<objects3D.size(); i++) {
            objects3D[i]->Render();
        }
    }
    void Scene::Destroy() {
        std::cout << "Scene:OnDestroy: Destroying scene" << std::endl;
        delete camera;
        OnDestroy();
        for(int i=0; i<objects3D.size(); i++) {
            objects3D[i]->Destroy();
            delete objects3D[i];
        }        
    }


    void Scene::OnKeyPressEvent(QKeyEvent *e){
        this->camera->OnKeyPressEvent(e);
    }
    void Scene::OnKeyReleaseEvent(QKeyEvent *e){
        this->camera->OnKeyReleaseEvent(e);
    }

    void Scene::OnMousePressEvent(QMouseEvent *e){
        this->camera->OnMousePressEvent(e);
    }

    void Scene::OnMouseReleaseEvent(QMouseEvent *e){
        this->camera->OnMouseReleaseEvent(e);
    }

    void Scene::OnMouseMoveEvent(QMouseEvent *e){
        this->camera->OnMouseMoveEvent(e);
    }

    void Scene::OnWheelEvent(QWheelEvent *e){
        this->camera->OnWheelEvent(e);
    }   

    void Scene::SetSkybox(std::vector<std::string> filenames) {
        parentWidget->makeCurrent();
        skyboxCubemap = Cubemap(filenames);
        hasSkybox = true;
        parentWidget->doneCurrent();
        triggerRefresh = true;
    }    

    
    void Scene::SetWindowSize(int w, int h) {
        this->windowWidth = w;
        this->windowHeight = h;
        float aspectRatio = (float)w/(float)h;

        // this->camera->SetAspect(aspectRatio);
        // this->camera->UpdateProjectionMatrix();
    }
}
}