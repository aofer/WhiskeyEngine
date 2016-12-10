#pragma once
#include "Core\Init\Init_GLFW.h"
#include "Core\Init\WindowInfo.h"
#include "Core/Init/Common.h"
#include "Managers\SceneManager.h"
#include "Managers\InputManager.h"

using namespace Core;
using namespace Init;


int main(int argc, char *argv[])
{
	WindowInfo window(std::string("Shadow Mapping Demo"), 400, 200, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	Core::ContextInfo context(4, 5, true);

	try{
		Core::Init::Init_GLFW glfwContext;
		glfwContext.Init(window,context);
		IListener* scene = new Managers::SceneManager();
		glfwContext.AddListener(scene);

		glfwContext.Run();

		delete scene;
	}
	catch (const std::exception& e){
		//log here
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}