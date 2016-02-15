#pragma once
#include "Core\Init\Init_GLFW.h"
#include "Core\Init\WindowInfo.h"
#include "Managers\SceneManager.h"
#include "Managers\InputManager.h"

using namespace Core;
using namespace Init;


int main(int argc, char *argv[])
{
	WindowInfo window(std::string("Whiskey engine test"), 400, 200, 800, 600, true);
	Core::ContextInfo context(4, 5, true);

	try{
		Core::Init::Init_GLFW glfwContext;
		glfwContext.Init(window,context);
		IListener* scene = new Managers::SceneManager();
		IListener* inputManager = new Managers::InputManager();
		glfwContext.AddListener(scene);
		glfwContext.AddListener(inputManager);

		glfwContext.Run();

		delete scene;
		delete inputManager;
	}
	catch (const std::exception& e){
		//log here
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}