#pragma once
#include <iostream>
#include "Init_GLEW.h"
#include <GLFW\glfw3.h>
#include "ContextInfo.h"
#include "WindowInfo.h"
#include "IListener.h"
#include <vector>


namespace Core
{
	namespace Init
	{
		class Init_GLFW
		{
		public:
			Init_GLFW();
			~Init_GLFW();

			//void error_callback(int error, const char* description);
			void Init(const Core::WindowInfo& window, const Core::ContextInfo& context);
			void Run(void);
			//static void Close();
			//void EnterFullscreen();
			//void ExitFullscreen();
			//static void PrintOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& context);
			void DisplayCallback(void);
		private:
			//static Core::IListener* listener;
			std::vector<Core::IListener*> m_listeners;
			Core::WindowInfo windowInformation;
			//static GLFWwindow* window;
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		public:
			//static void SetListener(Core::IListener*& iListener);
			void AddListener(Core::IListener* listener);

			double m_lastUpdate = 0.0;
		};
	}
}