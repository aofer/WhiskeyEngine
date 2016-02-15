#pragma once
#include "../Core/Init/IListener.h"
//#include "../Rendering/Camera.h"
namespace Managers
{
	class InputManager : public Core::IListener

	{
	public:
		InputManager();
		~InputManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previos_width, int previous_height);
		void update(float dt);
	private:

	};

}