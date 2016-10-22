#pragma once
namespace Core{

	class IInputListener
	{
	public:

		virtual void onKeyPressed(int key, int scancode) = 0;
		virtual void onKeyReleased(int key, int scancode) = 0;
	};

	}