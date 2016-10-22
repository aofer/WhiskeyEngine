#pragma once
#include "../Core/Init/IInputListener.h"
#include <vector>
//#include "../Rendering/Camera.h"
namespace Managers
{
	class InputManager 

	{
	public:
		static InputManager& getInstance()
		{
			static InputManager    instance; 			
			return instance;
		}

		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

		void update(float dt);
		
		void AddInputListener(Core::IInputListener* listener);

		void onKeyboardEvent(int key, int action, int scancode, int mods);
	private:

		InputManager() {}


		std::vector<Core::IInputListener*> m_inputListeners;
	};

}