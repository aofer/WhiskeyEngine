#pragma once
#include <glm/glm.hpp>
#include "../Core/Init/IInputListener.h"
#include "../Scene/Components/GameComponent.h"
/*
This class represents a basic camera with all of its camera controls
*/
namespace Rendering
{
	class BaseCamera : public Core::IInputListener, Scene::Components::GameComponent{
		private:

		float fieldOfView;
		float aspectRatio;
		float zNear;
		float zFar;

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

	protected:
		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 lookAt;
		void updateMatrices();

	public:
		//from game component
		virtual const Scene::Components::FamilyType GetFamilyType();

		//constructor
		BaseCamera();
		BaseCamera(float fieldOfView, float aspectRatio, float near, float far);
		//destructor
		~BaseCamera();
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



		virtual void Update(float dt);

	};

}
