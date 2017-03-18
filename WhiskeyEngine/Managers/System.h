#pragma once
namespace Managers
{
	/************************************************************************/
	/* This will serve as the basic interface for all the game engine systems */
	/************************************************************************/
	class System

	{
	public:

		virtual ~System() {}

		virtual void Update(float dt) = 0;
		virtual void Init(void) = 0;



	};

}