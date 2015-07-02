#pragma once
#include <iostream>
#include "Init_GLEW.h"
#include <GLFW\glfw3.h>
#include "ContextInfo.h"
#include "WindowInfo.h"
#include "IListener.h"


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
			static void Init(const Core::WindowInfo& window, const Core::ContextInfo& context);
			static void Run(void);
			//static void Close();
			//void EnterFullscreen();
			//void ExitFullscreen();
			//static void PrintOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& context);
			static void DisplayCallback(void);
		private:
			static Core::IListener* listener;
			static Core::WindowInfo windowInformation;
			//static GLFWwindow* window;
		public:
			static void SetListener(Core::IListener*& iListener);
		};
	}
}