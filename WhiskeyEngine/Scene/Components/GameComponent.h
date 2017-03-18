#pragma once

namespace Scene{
	
	class GameObject;

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


		class GameComponent
		{
		public:
			GameComponent(); //A hack to keep stuff compling - will be removed soon
			GameComponent(GameObject* owner);
			virtual ~GameComponent();
			virtual const FamilyType GetFamilyType() = 0 ;
			const GameObject* GetOwner() const;

			virtual void Update(float dt) = 0;

		private:
			GameObject* m_pOwner;

		};

	}

}