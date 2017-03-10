#pragma once

namespace Scene{

	namespace Components
	{
		enum class FamilyType
		{
			MESHES,
			RENDERING,
			PHYSICS,
			CAMERAS
		};

		typedef unsigned int go_id;
		typedef unsigned int go_priority;

		class GameComponent
		{
		public:

			GameComponent(go_priority priority);
			GameComponent();
			virtual ~GameComponent();
			virtual const FamilyType GetFamilyType() = 0 ;
			const go_priority GetPriority() const;
			virtual void Update(float dt) = 0;

		private:
			const go_priority m_priority; //Game objects will be updated by their given priority
		};

	}

}