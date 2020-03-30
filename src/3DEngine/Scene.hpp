#pragma once

#include "Common/Common.h"
#include "Component.hpp"
#include "Object3D.hpp"
#include "StandardShaders.hpp"
#include "Cubemap.hpp"
// #include "CameraScene.hpp"
#include "MeshFilterComponent.hpp"


namespace KikooRenderer {
class View3DGL;
namespace CoreEngine {
class Object3D;
class CameraScene;


class Scene {
    public: 
        Scene();
        virtual void Start();
		virtual void Render();
        virtual void Enable();
        // void Disable();
        void Destroy();
        bool started;

		std::vector<Object3D*> objects3D; 
		StandardShaders standardShaders;
		CameraScene* camera;

    	KikooRenderer::View3DGL* parentWidget;

		void virtual OnStart();  
		void virtual OnUpdate();
		void virtual OnRender(){};
		void virtual OnEnable(){};
		void virtual OnDisable(){};
		void virtual OnDestroy(){};
		
		virtual void OnKeyPressEvent(QKeyEvent *e);
		virtual void OnKeyReleaseEvent(QKeyEvent *e);
		virtual void OnMousePressEvent(QMouseEvent *e);
		virtual void OnMouseReleaseEvent(QMouseEvent *e);
		virtual void OnMouseMoveEvent(QMouseEvent *e);
		virtual void OnWheelEvent(QWheelEvent *event);       

		void SetWindowSize(int w, int h);

		int windowHeight;
		int windowWidth;

		bool triggerRefresh = true;

		clock_t time=0;
		float deltaTime;

		glm::vec3 bgColor = glm::vec3(0,0,0);

		//Scene skybox
		bool hasSkybox = false;
		void SetSkybox(std::vector<std::string> filenames);
		Cubemap skyboxCubemap;
		Object3D* skyboxCube;		
};



}
}