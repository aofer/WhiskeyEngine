#pragma once

namespace Scene{

	namespace Components
	{
		enum class FamilyType
		{
			MESHES,
			RENDERING,
			LIGHTING,
			PHYSICS,
			CAMERAS
		};

		typedef unsigned int gc_id;
		typedef unsigned int gc_priority;

		class GameComponent
		{
		public:

			GameComponent(gc_priority priority);
			GameComponent();
			virtual ~GameComponent();
			virtual const FamilyType GetFamilyType() = 0 ;
			const gc_priority GetPriority() const;
			virtual void Update(float dt) = 0;

		private:
			const gc_priority m_priority; //Game objects will be updated by their given priority
		};

	}

}