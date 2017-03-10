#pragma once
#include <glm/glm.hpp>
#include "../Core/Init/IInputListener.h"
#include "../Scene/Components/GameComponent.h"
/*
This class represents a basic camera with all of its camera controls
*/
namespace Rendering
{
	class Camera : public Core::IInputListener, Scene::Components::GameComponent{
	private:
		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 lookAt;
		float fieldOfView;
		float aspectRatio;
		float zNear;
		float zFar;

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;
		void updateMatrices();

	public:
		//from game component
		virtual const Scene::Components::FamilyType GetFamilyType();

		//constructor
		Camera();
		Camera(float fieldOfView, float aspectRatio, float near, float far);
		//destructor
		~Camera();
		//setters
		void setPosition(glm::vec3 position);
		void setUp(glm::vec3 up);
		void setLookAt(glm::vec3 lookAt);
		void setFieldOfView(float fov);
		void setAspectRatio(float aspectRatio);
		void setNear(float near);
		void setFar(float far);
		//getters
		glm::vec3 getPosition() const;
		glm::vec3 getUp() const;
		glm::vec3 getForward();
		glm::vec3 getRight();
		glm::vec3 getLookAt() const;
		float getFieldOfView() const;
		float getAspectRatio() const;
		float getNear() const;
		float getFar() const;
		glm::mat4 getProjection() const;
		glm::mat4 getView() const;
		glm::mat4 getViewProjection() const;

		//this method is used to move the camera forward and backwards in our scene
		void moveForward(float speed);
		//this method changes the pitch of the camera
		void pitch(float angle);
		//this method changes the yaw of the camera
		void yaw(float angle);
		//this method moves the camera left and right, like in an FPS game
		void strafe(float speed);
		//this method moves the camera up and down
		void liftUp(float speed);
		//this is the most important method in the camera, its used on our display function to update the camera matrices in openGL


		virtual void onKeyPressed(int key, int scancode);
		virtual void onKeyReleased(int key, int scancode);
		virtual void onKeyRepeated(int key, int scancode);
		void handleKey(int key);

		virtual void Update(float dt);

	};

}
