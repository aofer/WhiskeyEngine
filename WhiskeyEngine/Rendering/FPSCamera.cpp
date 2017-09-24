#include "FPSCamera.h"
//#include <glm/gtx/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h> //TODO remove this dependency

using namespace Scene::Components;

namespace Rendering
{


	FPSCamera::FPSCamera(float fieldOfView, float aspectRatio, float near, float far) : BaseCamera(fieldOfView, aspectRatio, near, far)
	{

	}

	FPSCamera::FPSCamera() : FPSCamera(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)
	{

	}

	FPSCamera::~FPSCamera()
	{

	}

	void FPSCamera::Update(float dt)
	{

	}
	
	void FPSCamera::moveForward(float speed)
	{
		// Get the current view vector (the direction we are looking)
		glm::vec3 vVector = getForward();

		position.x += vVector.x * speed;		// Add our acceleration to our position's X
		position.z += vVector.z * speed;		// Add our acceleration to our position's Z
		lookAt.x += vVector.x * speed;			// Add our acceleration to our view's X
		lookAt.z += vVector.z * speed;			// Add our acceleration to our view's Z
		updateMatrices();
	}


	void FPSCamera::pitch(float angle)
	{
		float PI = glm::pi<float>();
		float amount = std::sinf(angle * PI / 180);
		lookAt.y += amount;
		updateMatrices();
	}
	void FPSCamera::yaw(float angle)
	{
		float PI = glm::pi<float>();
		glm::vec3 rightVec = getRight();
		float radians = angle* PI / 180;
		lookAt.x = position.x + (lookAt.x - position.x) * std::cosf(radians) + (lookAt.z - position.z) * std::sinf(radians);
		lookAt.z = position.z + (lookAt.z - position.z) * std::cosf(radians) + (position.x - lookAt.x) * std::sinf(radians);
		updateMatrices();
	}



	void FPSCamera::strafe(float speed)
	{
		// Get our normalized right vector (The direction perpendicular to our view)
		glm::vec3 rightVector = getRight();

		// Move our FPSCamera position right or left along the right vector
		position.x += rightVector.x * speed;
		lookAt.x += rightVector.x * speed;
		position.z += rightVector.z * speed;
		lookAt.z += rightVector.z * speed;
		updateMatrices();
	}

	void FPSCamera::liftUp(float speed)
	{
		position.y += speed;
		lookAt.y += speed;
		updateMatrices();
	}

	void FPSCamera::onKeyRepeated(int key, int scancode)
	{
		handleKey(key);
	}
	void FPSCamera::onKeyReleased(int key, int scancode)
	{

	}

	void FPSCamera::onKeyPressed(int key, int scancode)
	{
		handleKey(key);
	}
	void FPSCamera::handleKey(int key)
	{
		if (key == GLFW_KEY_UP)
		{
			liftUp(0.5);
		}
		else if (key == GLFW_KEY_DOWN)
		{
			liftUp(-0.5);
		}
		else if (key == GLFW_KEY_A)
		{
			strafe(0.5);
		}
		else if (key == GLFW_KEY_D)
		{
			strafe(-0.5);
		}
		else if (key == GLFW_KEY_S)
		{
			moveForward(-0.5);
		}
		else if (key == GLFW_KEY_W)
		{
			moveForward(0.5);
		}
		else if (key == GLFW_KEY_R)
		{
			pitch(8.0);
		}
		else if (key == GLFW_KEY_F)
		{
			pitch(-8.0);
		}
		else if (key == GLFW_KEY_C)
		{
			yaw(1.6);
		}
		else if (key == GLFW_KEY_V)
		{
			yaw(-1.6);
		}
	}

}
