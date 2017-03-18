#pragma once
#include <vector>
#include <map>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include "Components/GameComponent.h"


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
		//enum class FamilyType;
	}
	typedef uint32_t go_id;
	
	class GameObject 
	{

	public:
		GameObject();
		GameObject(GameObject* parent);
		virtual ~GameObject();

		const glm::mat4& GetModelMatrix() const;
		const glm::vec3& GetPosition() const;
		const float& GetScale() const;
		const glm::quat& GetOrientation() const;
		const std::string& GetGOName() const;

		void SetOrientation(const glm::quat& orient);
		void SetPosition(const glm::vec3& position) ;
		void SetScale(const float& scale) ;
		void SetModel(Rendering::Models::Model* model);
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;
		Rendering::Models::Model* GetModel() const;
		void AddChild(GameObject* child);
		void Update(float dt);
		void AddGameComponent(const Components::FamilyType& familyType, Components::GameComponent* component);

		private:

			void UpdateModelMatrix();
			std::string m_goName;
			go_id		m_goId;
			glm::mat4 m_modelMatrix;
			glm::vec3 m_position;
			glm::quat m_orientation;
			float m_scale;
			Rendering::Models::Model* m_pModel; //Todo replace this when we add component system
			GameObject* m_pParent;
			std::vector<GameObject*> m_children;
			std::map<const Components::FamilyType, Components::GameComponent*> m_gameComponents;

	};
}