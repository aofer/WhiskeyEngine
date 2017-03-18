#include "GameComponent.h"

namespace Scene
{
	namespace Components
	{

		GameComponent::GameComponent():
			GameComponent(nullptr)
		{

		}

		GameComponent::GameComponent(GameObject* owner):
			m_pOwner(owner)
		{

		}

		GameComponent::~GameComponent()
		{
			m_pOwner = nullptr;
		}

		const GameObject* GameComponent::GetOwner() const
		{
			return m_pOwner;
		}


	}
}


