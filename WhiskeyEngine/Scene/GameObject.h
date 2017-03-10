#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>


namespace Rendering
{
	namespace Models
	{
		class Model;
	}
}
namespace Scene{

	namespace Components
	{
		class GameComponent;
	}
	
	class GameObject 
	{

	public:
		GameObject();
		GameObject(GameObject* parent);
		virtual ~GameObject();

		glm::mat4 GetModelMatrix() const;
		glm::vec3 GetPosition() const;
		float GetScale() const;
		glm::quat GetOrientation() const;

		void SetOrientation(const glm::quat& orient);
		void SetPosition(const glm::vec3& position) ;
		void SetScale(const float& scale) ;
		void SetModel(Rendering::Models::Model* model);
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;
		Rendering::Models::Model* GetModel() const;
		void AddChild(GameObject* child);
		void Update(float dt);

		private:

			void UpdateModelMatrix();

			glm::mat4 m_modelMatrix;
			glm::vec3 m_position;
			glm::quat m_orientation;
			float m_scale;
			Rendering::Models::Model* m_pModel; //Todo replace this when we add component system
			GameObject* m_pParent;
			std::vector<GameObject*> m_children;
			std::vector<Components::GameComponent*> m_gameComponents;

	};
}