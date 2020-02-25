#include "CameraScene.hpp"
#include "TransformComponent.hpp"
#include "Scene.hpp"
#include "CameraController.hpp"

namespace KikooRenderer {
namespace CoreEngine {


CameraScene::CameraScene(Scene* _scene, float _eyeDistance, float _fov, float _near, float _far, float _aspect) : Object3D("Camera", _scene, Shader()) {
    this->scene = _scene;
    this->eyeDistance = _eyeDistance;
    this->fov = _fov;
    this->nearClip = _near;
    this->farClip = _far;
    this->aspect = _aspect;

    UpdateProjectionMatrix();

    this->transform->position.x = 0;
    this->transform->position.y = 0;
    this->transform->position.z = -3;

	projectionType = ProjectionType::Perspective;
    viewMatrix = glm::inverse(this->transform->GetModelMatrix()); 

    orthoFOV = 10;

    cameraController = new CameraController(this);
}

glm::vec3 CameraScene::GetPosition() {
    return this->transform->position;
}

glm::mat4 CameraScene::GetProjectionMatrix() {
    return this->projectionMatrix;
}

glm::mat4 CameraScene::GetViewMatrix() {
    return glm::inverse(this->transform->GetModelMatrix());
}

glm::mat4 CameraScene::GetModelTransform() {
    return this->transform->GetModelMatrix();
}

void CameraScene::UpdateProjectionMatrix() {
	if(projectionType == ProjectionType::Perspective)  this->projectionMatrix = glm::perspectiveLH(this->fov, this->aspect, this->nearClip, this->farClip);     
	else this->projectionMatrix = glm::orthoLH(-orthoFOV * this->aspect, orthoFOV * this->aspect, -orthoFOV, orthoFOV, 0.0001f, this->farClip);
}

void CameraScene::OnKeyReleaseEvent(QKeyEvent *e){
    cameraController->OnKeyReleaseEvent(e);
}

void CameraScene::OnUpdate(){
    transform->OnUpdate();
    cameraController->OnUpdate();
}

void CameraScene::OnKeyPressEvent(QKeyEvent *e){
    
    cameraController->OnKeyPressEvent(e);
	if (e->key() == Qt::Key_5) {
		if (projectionType == ProjectionType::Perspective) projectionType = ProjectionType::Orthographic;
		else projectionType = ProjectionType::Perspective;
			
		UpdateProjectionMatrix();

	}
    previousViewMatrix = glm::mat4(viewMatrix);
    viewMatrix = glm::inverse(this->transform->GetModelMatrix());
}

void CameraScene::OnMousePressEvent(QMouseEvent *e) {
    cameraController->OnMousePressEvent(e);
}
void CameraScene::OnMouseReleaseEvent(QMouseEvent *e) {
    cameraController->OnMouseReleaseEvent(e);
}
void CameraScene::OnMouseMoveEvent(QMouseEvent *e) {
    cameraController->OnMouseMoveEvent(e);

    previousViewMatrix = glm::mat4(viewMatrix);
    viewMatrix = glm::inverse(this->transform->GetModelMatrix());
}
void CameraScene::OnWheelEvent(QWheelEvent *e) {
    cameraController->OnWheelEvent(e);

    UpdateProjectionMatrix();
    previousViewMatrix = glm::mat4(viewMatrix);
    viewMatrix = glm::inverse(this->transform->GetModelMatrix());
}



//Accessors
float CameraScene::GetEyeDistance() {
    return eyeDistance;
}

void  CameraScene::SetEyeDistance(float value) {
    this->eyeDistance = value;
}

float CameraScene::GetFov() {
    return fov;
}

void  CameraScene::SetFov(float value) {
    this->fov = value;
}

float CameraScene::GetNearClip() {
    return nearClip;
}

void  CameraScene::SetNearClip(float value) {
    this->nearClip = value;
}

float CameraScene::GetFarClip() {
    return farClip;
}

void  CameraScene::SetFarClip(float value) {
    this->farClip = value;
}

float CameraScene::GetAspect() {
    return aspect;
}

void  CameraScene::SetAspect(float value) {
    this->aspect = value;
}


void  CameraScene::SetProjectionMatrix(glm::mat4 value) {
    this->projectionMatrix = value;
}

void  CameraScene::SetViewMatrix(glm::mat4 value) {
    this->viewMatrix = value;
}

glm::mat4 CameraScene::GetPreviousViewMatrix() {
    return previousViewMatrix;
}

void  CameraScene::SetPreviousViewMatrix(glm::mat4 value) {
    this->previousViewMatrix = value;
}

CameraController* CameraScene::GetCameraController() {
    return cameraController;
}

void  CameraScene::SetCameraController(CameraController* value) {
    this->cameraController = value;
}

float CameraScene::GetOrthoFOV() {
    return orthoFOV;
}

void  CameraScene::SetOrthoFOV(float value) {
    this->orthoFOV = value;
}

float CameraScene::GetSpeedFactor() {
    return speedFactor;
}

void  CameraScene::SetSpeedFactor(float value) {
    this->speedFactor = value;
}


}
}