#include "BaseCamera.h"
//#include <glm/gtx/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h> //TODO remove this dependency

using namespace Scene::Components;

namespace Rendering
{
	const FamilyType BaseCamera::GetFamilyType()
	{
		return FamilyType::CAMERAS;
	}


	BaseCamera::BaseCamera(float fieldOfView, float aspectRatio, float near, float far) : fieldOfView(fieldOfView), aspectRatio(aspectRatio), zNear(near), zFar(far)
	{
		up = glm::vec3(0.0, 1.0, 0.0);
		position = glm::vec3(0.0, 0.0, 0.0);
		lookAt = glm::vec3(0.0, 0.0, -1.0);
	}

	BaseCamera::BaseCamera() : BaseCamera(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)
	{

	}

	BaseCamera::~BaseCamera()
	{

	}

	void BaseCamera::Update(float dt)
	{

	}

	//setters
	void BaseCamera::setPosition(glm::vec3 position)
	{
		this->position = position;
		updateMatrices();
	}

	void BaseCamera::setUp(glm::vec3 up){
		this->up = up;
		updateMatrices();

	}

	void BaseCamera::setLookAt(glm::vec3 lookAt)
	{
		this->lookAt = lookAt;
		updateMatrices();
	}

	void BaseCamera::setFieldOfView(float fov)
	{
		this->fieldOfView = fieldOfView;
		updateMatrices();
	}

	void BaseCamera::setAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
		updateMatrices();
	}

	void BaseCamera::setNear(float near)
	{
		this->zNear = near;
		updateMatrices();
	}

	void BaseCamera::setFar(float far)
	{
		this->zFar = far;
		updateMatrices();
	}

	//getters
	glm::vec3 BaseCamera::getPosition() const
	{
		return position;
	}

	glm::vec3 BaseCamera::getUp() const
	{
		return up;
	}

	glm::vec3 BaseCamera::getLookAt() const
	{
		return lookAt;
	}

	float BaseCamera::getFieldOfView() const
	{
		return fieldOfView;
	}

	float BaseCamera::getAspectRatio() const
	{
		return aspectRatio;
	}

	float BaseCamera::getNear() const
	{
		return zNear;
	}

	float BaseCamera::getFar() const
	{
		return zFar;
	}
	//returns the normalized forward vector
	glm::vec3 BaseCamera::getForward()
	{
		glm::vec3 fVector = glm::normalize(lookAt - position);
		return fVector;
	}

	glm::vec3 BaseCamera::getRight()
	{
		return glm::cross(glm::normalize(up),getForward());
	}

	glm::mat4 BaseCamera::getProjection() const
	{
		return projectionMatrix;
	}
	glm::mat4 BaseCamera::getView() const
	{
		return viewMatrix;
	}
	glm::mat4 BaseCamera::getViewProjection() const
	{
		return viewProjectionMatrix;
	}


	void BaseCamera::updateMatrices()
	{

		projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, zNear, zFar);

		viewMatrix = glm::lookAt(position, lookAt, up);
		viewProjectionMatrix = projectionMatrix * viewMatrix;

	}

}
