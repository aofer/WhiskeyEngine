#include "Camera.h"
#include <glm/gtx/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h> //TODO remove this dependency


namespace Rendering
{

	Camera::Camera(float fieldOfView, float aspectRatio, float near, float far) : fieldOfView(fieldOfView), aspectRatio(aspectRatio), zNear(near), zFar(far) 
	{
		up = glm::vec3(0.0, 1.0, 0.0);
		position = glm::vec3(0.0, 0.0, 0.0);
		lookAt = glm::vec3(0.0, 0.0, -1.0);
	}

	Camera::Camera() : Camera(45.0, 4.0 / 3.0, 0.01f, 100.0f)
	{

	}

	Camera::~Camera()
	{

	}

	//setters
	void Camera::setPosition(glm::vec3 position)
	{
		this->position = position;
		updateMatrices();
	}

	void Camera::setUp(glm::vec3 up){
		this->up = up;
		updateMatrices();

	}

	void Camera::setLookAt(glm::vec3 lookAt)
	{
		this->lookAt = lookAt;
		updateMatrices();
	}

	void Camera::setFieldOfView(float fov)
	{
		this->fieldOfView = fieldOfView;
		updateMatrices();
	}

	void Camera::setAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
		updateMatrices();
	}

	void Camera::setNear(float near)
	{
		this->zNear = near;
		updateMatrices();
	}

	void Camera::setFar(float far)
	{
		this->zFar = far;
		updateMatrices();
	}

	//getters
	glm::vec3 Camera::getPosition() const
	{
		return position;
	}

	glm::vec3 Camera::getUp() const
	{
		return up;
	}

	glm::vec3 Camera::getLookAt() const
	{
		return lookAt;
	}

	float Camera::getFieldOfView() const
	{
		return fieldOfView;
	}

	float Camera::getAspectRatio() const
	{
		return aspectRatio;
	}

	float Camera::getNear() const
	{
		return zNear;
	}

	float Camera::getFar() const
	{
		return zFar;
	}
	//returns the normalized forward vector
	glm::vec3 Camera::getForward()
	{
		glm::vec3 fVector = glm::normalize(lookAt - position);
		return fVector;
	}

	glm::vec3 Camera::getRight()
	{
		return glm::cross(glm::normalize(up),getForward());
	}

	glm::mat4 Camera::getProjection() const
	{
		return projectionMatrix;
	}
	glm::mat4 Camera::getView() const
	{
		return viewMatrix;
	}
	glm::mat4 Camera::getViewProjection() const
	{
		return viewProjectionMatrix;
	}

	void Camera::moveForward(float speed)
	{
		// Get the current view vector (the direction we are looking)
		glm::vec3 vVector = getForward();

		position.x += vVector.x * speed;		// Add our acceleration to our position's X
		position.z += vVector.z * speed;		// Add our acceleration to our position's Z
		lookAt.x += vVector.x * speed;			// Add our acceleration to our view's X
		lookAt.z += vVector.z * speed;			// Add our acceleration to our view's Z
		updateMatrices();
	}


	void Camera::pitch(float angle)
	{
		float PI = glm::pi<float>();
		float amount = std::sinf(angle * PI / 180);
		lookAt.y += amount;
		updateMatrices();
	}
	void Camera::yaw(float angle)
	{
		float PI = glm::pi<float>();
		glm::vec3 rightVec = getRight();
		float radians = angle* PI / 180;
		lookAt.x = position.x + (lookAt.x - position.x) * std::cosf(radians) + (lookAt.z - position.z) * std::sinf(radians);
		lookAt.z = position.z + (lookAt.z - position.z) * std::cosf(radians) + (position.x - lookAt.x) * std::sinf(radians);
		updateMatrices();
	}

	void Camera::updateMatrices()
	{

//		projectionMatrix = glm::perspective(fieldOfView, aspectRatio, zNear, zFar);
		projectionMatrix[0][0] = 1.0f / (aspectRatio * glm::tan(fieldOfView / 2.0f));
		projectionMatrix[1][1] = 1.0f / glm::tan(fieldOfView / 2.0f);
		projectionMatrix[2][2] = (-zNear - zFar) / (zNear - zFar);
		projectionMatrix[2][3] = 1.0f;
		projectionMatrix[3][2] = 2.0f * zNear * zFar / (zNear - zFar);


		viewMatrix = glm::lookAt(position, lookAt, up);
		viewProjectionMatrix = projectionMatrix * viewMatrix;

	}

	void Camera::strafe(float speed)
	{
		// Get our normalized right vector (The direction perpendicular to our view)
		glm::vec3 rightVector = getRight();

		// Move our camera position right or left along the right vector
		position.x += rightVector.x * speed;
		lookAt.x += rightVector.x * speed;
		position.z += rightVector.z * speed;
		lookAt.z += rightVector.z * speed;
		updateMatrices();
	}

	void Camera::liftUp(float speed)
	{
		position.y += speed;
		lookAt.y += speed;
		updateMatrices();
	}

	void Camera::onKeyPressed(int key, int scancode)
	{
		if (key == GLFW_KEY_UP)
		{
			liftUp(0.1);
		}
		else if (key == GLFW_KEY_DOWN)
		{
			liftUp(-0.1);
		}
		else if (key == GLFW_KEY_LEFT)
		{
			strafe(0.2);
		}
		else if (key == GLFW_KEY_RIGHT)
		{
			strafe(-0.2);
		}
		else if (key == GLFW_KEY_A)
		{
			moveForward(0.1);
		}
		else if (key == GLFW_KEY_Q)
		{
			moveForward(-0.1);
		}
		else if (key == GLFW_KEY_W)
		{
			pitch(0.1);
		}
		else if (key == GLFW_KEY_S)
		{
			pitch(-0.1);
		}
		else if (key == GLFW_KEY_Z)
		{
			yaw(0.1);
		}
		else if (key == GLFW_KEY_X)
		{
			yaw(-0.1);
		}
	}
	void Camera::onKeyReleased(int key, int scancode)
	{

	}


}
