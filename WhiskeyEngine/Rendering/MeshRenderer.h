#pragma once
#include "../Scene/Components/GameComponent.h"

namespace Rendering
{
	class GameObject;
	//struct FamilyType;
	class MeshRenderer : public Scene::Components::GameComponent
	{
	public:
		MeshRenderer(); //A hack to keep stuff compling - will be removed soon
		MeshRenderer(GameObject* owner);
		virtual ~MeshRenderer();

		virtual const Scene::Components::FamilyType GetFamilyType()
		{
			return Scene::Components::FamilyType::RENDERING;
		}

		virtual void Update(float dt) = 0;
	};
}