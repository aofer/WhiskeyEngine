#include "GameComponent.h"

namespace Scene
{
	namespace Components
	{
		GameComponent::GameComponent(gc_priority priority):
			m_priority(priority)
		{

		}

		GameComponent::GameComponent():
			m_priority(1)
		{

		}

		GameComponent::~GameComponent()
		{

		}

		const gc_priority GameComponent::GetPriority() const
		{
			return m_priority;
		}

	}
}


